/**
 * 
 */
package mades.environment;

import java.util.HashMap;

import mades.cosimulation.Cosimulator;

/**
 * 
 * @author Michele Sama (m.sama@puzzledev.com)
 *
 * Defines the interface between the {@link Cosimulator} and the environment.
 * Implementations of this interface allow the {@link Cosimulator} to initialize
 * the environment simulation tool and to control it during the simulation. 
 */
public interface EnvironmentConnector {

	/**
	 * Initializes the environment simulator with a set of configuration
	 * parameters given by the Cosimulator. This initialization has to be done
	 * once and only once.
	 * 
	 * @param params: A collection of key,value initialization parameters.
	 */
	public void initialize(HashMap<String, String> params);
	
	/**
	 * Loads a given initial state to the environment. This method is supposed
	 * to be invoked ad each step of the co-simulation.
	 * 
	 * @param system: The initial configuration of the system. 
	 * @param environment: The initial configuration of the environment. 
	 *         If <code>null</code> the last simulated step is used.
	 * @throws IllegalArgumentException: If <code>environment</code> is
	 *         <code>null</code> and if no simulation steps have been 
	 *         performed.
	 */
	public void load(HashMap<String, String> system,
			HashMap<String, String> environment);
	
	/**
	 * Performs the next step of the simulation.
	 * 
	 * @param time: The time to simulate.
	 * @return The result of the simulation.
	 * @throws IllegalArgumentException: If time is negative or lesser 
	 *         than the last simulated step.
	 */
	public HashMap<String, String> simulateNext(double time);
	
	/**
	 * Returns the value of the current step of the simulation. The returned
	 * value is the same as the last simulated step.
	 * 
	 * @return The result of the last performed step of the simulation. If no
	 *         simulation has been performed it returns an empty collection.
	 * @throws AssertionError: If no simulation step has been performed.
	 */
	public HashMap<String, String> getCurrentParams();
}
