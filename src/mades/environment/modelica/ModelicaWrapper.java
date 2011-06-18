/**
 * 
 */
package mades.environment.modelica;

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
import mades.common.variables.Scope;
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
	private static String BASE_FILE_POSTFIX = "_variables.txt";
	private static String FINAL_FILE_POSTFIX = "_final.txt";
	private static String SIGNAL_FILE_NAME = "A_Transitions";
	private static String RUN_FILE = "run.sh";
	
	private static final String VARIABLE_NAME = "[ ]*[\\w -\\._\\(\\)]+";
	private static final String DOUBLE = "[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?";
	private static final String LABEL = "(\"[\\w\\W]+\")";
	private static final String VARIABLE_LINE = "^("  + DOUBLE + "|" + LABEL + ")( //[ ]*(default))? //(" + VARIABLE_NAME + ")$";
	private Pattern variablePattern = Pattern.compile(VARIABLE_LINE);
	
	private static final String SIGNAL_LINE = "^(TRANSnp|TRANSpn):\\t(" + VARIABLE_NAME + ")\\t(" + DOUBLE + ")$";
	private Pattern signalPattern = Pattern.compile(SIGNAL_LINE);
	
	private String environmentPath;
	
	private String environmentFileName;
	private String runFileName;
	private String initialVariableFileName;
	private String baseVariableFileName;
	private String finalVariableFileName;
	private String signalsFileName;
	
	private VariableFactory variableFactory;
	private Clock clock;
	
	private int numVariables;
	
	/**
	 * @param environmentPath
	 * @param environmentName
	 */
	protected ModelicaWrapper(String environmentPath, Clock clock) {
		this.environmentPath = environmentPath;
		
		this.clock = clock;
		
		File folder = new File(environmentPath);
		
		environmentFileName = environmentPath + File.separator + folder.getName();
		baseVariableFileName = environmentFileName + BASE_FILE_POSTFIX;
		initialVariableFileName = environmentFileName + INIT_FILE_POSTFIX;
		// Copy the base variables in the initial file
		copy(baseVariableFileName, initialVariableFileName);
		
		finalVariableFileName = environmentFileName + FINAL_FILE_POSTFIX;
		signalsFileName = environmentPath + File.separator + SIGNAL_FILE_NAME;
		runFileName = environmentPath + File.separator + RUN_FILE;
	}
	
	
	protected void copy(String fileSource, String fileDest) {
		File source = new File(fileSource);
		if (!source.isFile()) {
			throw new AssertionError("Source file is not a file: " + fileSource);
		}
		if (!source.canRead()) {
			throw new AssertionError("Cannot read source file: " + fileSource);
		}
		
		File dest = new File(fileDest);
		if (!dest.exists()) {
			try {
				dest.createNewFile();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		if (!dest.canWrite()) {
			throw new AssertionError("Cannot write destintion file: " + fileDest);
		}
		try {
			BufferedReader reader = new BufferedReader(new FileReader(source));
			PrintWriter writer = new PrintWriter(dest);
			String line;
			try {
				while ((line = reader.readLine()) != null) {
					writer.println(line);
				}
			} catch (IOException e) {
				e.printStackTrace();
			} finally {
				writer.flush();
				writer.close();
			}
		
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
	}
	
	/**
	 * Initialize this wrapper by reading the init file.
	 * The init file contains variables and their initial value but not
	 * their scope. All the variable defined in the init file but not
	 * already defined in the co-simulation are considered internal.
	 * 
	 * @param variableFactory A factory containing all the variables 
	 *         already defined.
	 * @return the initial state of this environment.
	 */
	public EnvironmentMemento initFromFile(VariableFactory variableFactory) {
		this.variableFactory = variableFactory;
		ArrayList<VariableAssignment> variables = new ArrayList<VariableAssignment>();
		numVariables = 0;
		
		try {
			BufferedReader reader = new BufferedReader(new FileReader(baseVariableFileName));
			String line = null;
			while ((line = reader.readLine()) != null) {
				Matcher matcher = variablePattern.matcher(line);
				if (matcher.matches()) {
					String value = matcher.group(1);
					String annotation = matcher.group(5);
					String name = matcher.group(6);
					VariableDefinition def = null;
					if (!variableFactory.isDefined(name)) {
						// All modelica variables are double
						def = variableFactory.define(name, Scope.ENVIRONMENT_INTERNAL, false);
					}
					else {
						def = variableFactory.get(name);
					}
					
					if (name.equals(START_TIME_VAR_NAME)) {
						value = "0";
					} else if (name.equals(END_TIME_VAR_NAME)) {
						value = "" + clock.getTimeStep();
					}
					
					VariableAssignment var = new VariableAssignment(def, value);
					var.setAnnotation(annotation);
					variables.add(var);
				} else {
					System.out.println("** Skipped line: " + line);
				}
				numVariables ++;
			}
			reader.close();
		} catch (FileNotFoundException e1) {
			e1.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		deleteSignalFile();
		
		EnvironmentMemento memento = new EnvironmentMemento(clock.getCurrentTime(), variables, new SignalMap());
		return memento;
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
				String name = v.getVariableDefinition().getName();
				String annotation = v.getAnnotation();
				String value = v.getValue();
				// Update simulation time
				if (name.equals(START_TIME_VAR_NAME)) {
					value = "" + (clock.getCurrentTime().getSimulationTime() - clock.getTimeStep());
				} else if (name.equals(END_TIME_VAR_NAME)) {
					value = "" + (clock.getCurrentTime().getSimulationTime());
				}
				if (annotation != null) {
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
		Runtime run = Runtime.getRuntime();
		Process process = null;
		try {
			process = run.exec(runFileName + " " + environmentPath);
		} catch (IOException e) {
			e.printStackTrace();
		}
		try {
			process.waitFor();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		BufferedReader buf = new BufferedReader(
				new InputStreamReader(process.getInputStream()));
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
			BufferedReader reader = new BufferedReader(new FileReader(finalVariableFileName));
			String line = null;

			
			while ((line = reader.readLine()) != null) {
				Matcher matcher = variablePattern.matcher(line);
				if (matcher.matches()) {
					String value = matcher.group(1);
					String annotation = matcher.group(5);
					String name = matcher.group(6);
					VariableDefinition def = variableFactory.get(name);
					
					if (name.equals(START_TIME_VAR_NAME)) {
						startTime = Double.parseDouble(value);
						value = "" + (clock.getCurrentTime().getSimulationTime() - clock.getTimeStep());
					} else if (name.equals(END_TIME_VAR_NAME)) {
						endTime = Double.parseDouble(value);
						value = "" + clock.getCurrentTime().getSimulationTime();
					}
					
					VariableAssignment var = new VariableAssignment(def, value);
					var.setAnnotation(annotation);
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
		
		
		EnvironmentMemento resultMemento = new EnvironmentMemento(clock.getCurrentTime(), variables, memento.getSignals());
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
