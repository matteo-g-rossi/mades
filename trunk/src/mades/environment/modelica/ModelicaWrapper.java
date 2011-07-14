/**
 * 
 */
package mades.environment.modelica;

import static mades.common.utils.Runtimes.runCommand;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import mades.common.timing.Clock;
import mades.common.variables.Trigger;
import mades.common.variables.VariableAssignment;
import mades.common.variables.VariableDefinition;
import mades.common.variables.VariableFactory;
import mades.environment.EnvironmentMemento;
import mades.environment.SignalMap;

/**
 * @author Michele Sama (m.sama@puzzledev.com)
 *
 * Wrapper class for using modelica exported system as
 * simulator for the environment.
 *
 */
public class ModelicaWrapper {

	private final static double TOLERANCE = 0.00000001;
	
	public static final Object START_TIME_VAR_NAME = " start value";
	public static final Object END_TIME_VAR_NAME = " stop value";
	private static String INIT_FILE_POSTFIX = "_init.txt";
	private static String FINAL_FILE_POSTFIX = "_final.txt";
	private static String SIGNAL_FILE_NAME = "A_Transitions";
	private static String RUN_FILE = "./env/modelica.sh";
	
	private static final String VARIABLE_NAME = "[ ]*[\\w -\\._\\(\\)]+";
	private static final String DOUBLE = "[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?";
	private static final String LABEL = "(\"[\\w\\W]+\")";
	private static final String VARIABLE_LINE = "^("  + DOUBLE + "|" + LABEL + ")( //[ ]*(default))? //(" + VARIABLE_NAME + ")$";
	private Pattern variablePattern = Pattern.compile(VARIABLE_LINE);
	
	private static final String SIGNAL_LINE = "^(TRANSnp|TRANSpn):\\t(" + VARIABLE_NAME + ")\\t(" + DOUBLE + ")$";
	private Pattern signalPattern = Pattern.compile(SIGNAL_LINE);
	
	private String environmentFolder;
	private String environmentName;
	
	private String initialVariableFileName;
	private String finalVariableFileName;
	private String signalsFileName;
	
	private VariableFactory variableFactory;
	private Clock clock;
	
	private int numVariables;
	
	/**
	 * @param environmentPath
	 * @param environmentName
	 */
	protected ModelicaWrapper(String environmentPath, Clock clock,
			VariableFactory variableFactory, ArrayList<Trigger> triggers) {
		this.variableFactory = variableFactory;
		this.clock = clock;
		
		File folder = new File(environmentPath);
		
		environmentFolder = environmentPath ;
		environmentName = folder.getName();
		
		
		initialVariableFileName = environmentFolder + 
				File.separator + environmentName + INIT_FILE_POSTFIX;
		finalVariableFileName = environmentFolder +
				File.separator + environmentName + FINAL_FILE_POSTFIX;
		signalsFileName = environmentPath + File.separator + SIGNAL_FILE_NAME;
		
		ModelInstrumentor instrumentor = new ModelInstrumentor(environmentPath + File.separator +
				"sources" + File.separator + environmentName + ".mo");
		instrumentor.checkAndUpdateModel(triggers);
		instrumentor.compile();
	}
	
	public EnvironmentMemento initialize(
			EnvironmentMemento environmentMemento) {
		numVariables = environmentMemento.getParams().size();
		// TODO(rax): check initial variables
		/*
		ArrayList<VariableAssignment> variables = environmentMemento.getParams();
		for (VariableAssignment v: variables) {
			String name = v.getVariableDefinition().getEnvironmentName();
			if (name.equals(START_TIME_VAR_NAME)) {
				v. = "0";
			} else if (name.equals(END_TIME_VAR_NAME)) {
				value = "" + clock.getTimeStep();
			}
		}*/
		return environmentMemento;
	} 
	
		
	private void deleteSignalFile() {
		File signalFile = new File(signalsFileName);
		if (signalFile.exists()) {
			signalFile.delete();
		}
	}
	
	
	public EnvironmentMemento simulateNext(EnvironmentMemento memento) {
		writeVariablesFromMemento(memento);
		deleteSignalFile();
		runModelica(memento);
		return loadVariablesFromSimulation(memento);
	}
	
	protected void writeVariablesFromMemento(EnvironmentMemento memento) {
		ArrayList<VariableAssignment> variables = memento.getParams();
		try {
			PrintWriter writer = new PrintWriter(initialVariableFileName);
			
			for (VariableAssignment v: variables) {
				String name = v.getVariableDefinition().getEnvironmentName();
				String annotation = v.getAnnotation();
				String value = v.getValue();
				// Update simulation time
				if (name.equals(START_TIME_VAR_NAME)) {
					value = "" + (clock.getCurrentTime().getSimulationTime() - 
							clock.getTimeStep());
				} else if (name.equals(END_TIME_VAR_NAME)) {
					value = "" + (clock.getCurrentTime().getSimulationTime());
				}
				// Format output values
				switch (v.getVariableDefinition().getType()) {
					case STRING: {
						break;
					}
					case INTEGER: {
						value = Integer.parseInt(value) + "";
						break;
					}
					case DOUBLE: {
						value = Double.parseDouble(value) + "";
						break;
					}
					case BOOLEAN: {
						break;
					}
				
				}
				
				if (!annotation.equals("")) {
					writer.println(value + " //" + annotation +" //" +name);
				}else {
					writer.println(value + " //" + name);
				}
			}
			writer.flush();
			writer.close();

		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		
	}
	
	protected void runModelica(EnvironmentMemento memento) {
		BufferedReader buf = new BufferedReader(
				new InputStreamReader(
						runCommand(RUN_FILE + " " +
								environmentFolder + " " + environmentName)));
		
		String line = "";
		try {
			while ((line=buf.readLine())!=null) {
				System.out.println(line);
			}
		} catch (IOException e) {
			e.printStackTrace();
		} 
	}
	
	protected EnvironmentMemento loadVariablesFromSimulation(EnvironmentMemento memento) {
		ArrayList<VariableAssignment> variables = new ArrayList<VariableAssignment>();
		
		
		double startTime = 0;
		double endTime = 0;
		
		try {
			BufferedReader reader = new BufferedReader(
					new FileReader(finalVariableFileName));
			String line = null;

			
			while ((line = reader.readLine()) != null) {
				Matcher matcher = variablePattern.matcher(line);
				if (matcher.matches()) {
					String value = matcher.group(1);
					String annotation = matcher.group(5);
					String name = matcher.group(6);
					VariableDefinition def = variableFactory.getEnvironmentVar(name);
					
					if (name.equals(START_TIME_VAR_NAME)) {
						startTime = Double.parseDouble(value);
						value = "" + (clock.getCurrentTime().getSimulationTime() - 
								clock.getTimeStep());
					} else if (name.equals(END_TIME_VAR_NAME)) {
						endTime = Double.parseDouble(value);
						value = "" + clock.getCurrentTime().getSimulationTime();
					}
					
					if (annotation == null) {
						annotation = "";
					}
					
					VariableAssignment var = new VariableAssignment(def, value, annotation);
					variables.add(var);
				} else {
					System.out.println("** Skipped line: " + line);
				}
			}
			reader.close();
		} catch (FileNotFoundException e1) {
			e1.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		// TODO(rax): use modelica variable " tolerance";
		if (Math.abs(endTime - startTime) > TOLERANCE) {
			throw new AssertionError("Incomplete simulation");
		}
		
		if (variables.size() != numVariables) {
			throw new AssertionError(
				    "Wrong number of loaded variables. Found: " + 
				    variables.size() + " Expected: " + 
				    numVariables);
		}
		
		
		EnvironmentMemento resultMemento = new EnvironmentMemento(
				clock.getCurrentTime(), variables, memento.getSignals());
		File signalsFile = new File(signalsFileName);
		if (signalsFile.isFile() && signalsFile.exists()) {
			try {
				BufferedReader reader = new BufferedReader(new FileReader(signalsFile));
				String line = null;
				while ((line = reader.readLine()) != null) {
					parseSignalLine(resultMemento.getSignals(), line);
				}
				reader.close();
			} catch (FileNotFoundException e) {
				e.printStackTrace();
			} catch (IOException e) {
				e.printStackTrace();
			}
			
		}
		return resultMemento;
	}
	
	protected void parseSignalLine(SignalMap signals, String line) {
		Matcher matcher = signalPattern.matcher(line);
		if (matcher.matches()) {
			String upDown = matcher.group(1);
			String name = matcher.group(2);
			String value = matcher.group(3);
			signals.put(name, Double.parseDouble(value));
		}
	}
}