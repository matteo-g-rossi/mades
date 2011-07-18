package mades.environment.modelica;

import static org.junit.Assert.*;

import java.util.ArrayList;
import java.util.logging.Logger;

import mades.common.timing.Clock;
import mades.common.variables.Scope;
import mades.common.variables.VariableAssignment;
import mades.common.variables.VariableDefinition;
import mades.common.variables.VariableFactory;
import mades.environment.EnvironmentMemento;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

public class ModelicaWrapperTestCase {

	public final static String PATH = "./examples/RC/";
	
	VariableDefinition cond1;
	VariableDefinition react1;
	VariableDefinition act1;
	
	Clock clock;
	ModelicaWrapper wrapper;
	VariableFactory variableFactory = new VariableFactory();
	
	@Before
	public void setUp() throws Exception {
		clock = new Clock(Logger.getLogger(ModelicaWrapperTestCase.class.getName()), 
				10, 0, 30);
		
		cond1 = variableFactory.define("COND1", Scope.ENVIRONMENT_SHARED, true);
		react1 = variableFactory.define("REACT1", Scope.SYSTEM_SHARED, true);
		act1 = variableFactory.define("ACT1", Scope.SYSTEM_INTERNAL, true);
		
		wrapper = new ModelicaWrapper(PATH, clock);
		
	}

	@After
	public void tearDown() throws Exception {
	}

	protected void assertInitialStartStopTime(EnvironmentMemento memento) {
		ArrayList<VariableAssignment> variables = memento.getParams();
		for (VariableAssignment v: variables) {
			if (ModelicaWrapper.START_TIME_VAR_NAME.equals(
					v.getVariableDefinition().getName())) {
				assertEquals("0", v.getValue());
			} else if(ModelicaWrapper.END_TIME_VAR_NAME.equals(
					v.getVariableDefinition().getName())) {
				assertEquals(
						"" + clock.getTimeStep(),
						v.getValue()
						);
			}
		}
	}
	
	protected void assertStartStopTime(EnvironmentMemento memento) {
		ArrayList<VariableAssignment> variables = memento.getParams();
		for (VariableAssignment v: variables) {
			if (ModelicaWrapper.START_TIME_VAR_NAME.equals(
					v.getVariableDefinition().getName())) {
				assertEquals(
						"" + (clock.getCurrentTime().getSimulationTime() - clock.getTimeStep()),
						v.getValue());
			} else if(ModelicaWrapper.END_TIME_VAR_NAME.equals(
					v.getVariableDefinition().getName())) {
				assertEquals(
						"" + clock.getCurrentTime().getSimulationTime(),
						v.getValue());
			}
		}
	}
	
	@Test
	public void testInitFromFile() {
		EnvironmentMemento memento = wrapper.initFromFile(variableFactory);
		assertInitialStartStopTime(memento);
	}

	@Test
	public void testSimulateNext() {
		EnvironmentMemento memento = wrapper.initFromFile(variableFactory);
		assertInitialStartStopTime(memento);
		clock.tickForward();
		memento = wrapper.simulateNext(memento);
		assertStartStopTime(memento);
		clock.tickForward();
		memento = wrapper.simulateNext(memento);
		assertStartStopTime(memento);
	}


	@Test
	public void testParseSignalLine() {
		fail("Not yet implemented");
	}

}