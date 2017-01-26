/**
 * @file AccountDelegate.java
 * @author Ronald T. Fernandez
 * @version 1.0
 */
package utils;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Properties;
import java.util.StringTokenizer;
import java.util.Vector;

import corbaAccount.operationType;

public class Utils {

	/**
	 * Define the type of possible account operations
	 */
	public static enum OperationType {ADD, WITHDRAW}
	
	/**
	 * Convert an Utils.OperationType to a CORBA operationType
	 * @param opType	Utils.OperationType to be converted
	 * @return Returns the equivalent CORBA operationType
	 */
	public static operationType convertType(OperationType opType) {
		switch (opType) {
		case ADD:
			return operationType.ADD;
		case WITHDRAW:
			return operationType.WITHDRAW;
		default:
			throw new RuntimeException("Type not valid");
		}
	}
	
	/**
	 * Convert a CORBA operationType to a Utils.OperationType
	 * @param opType	CORBA operationType to be converted
	 * @return Returns the equivalent Utils OperationType
	 */	
	public static OperationType convertType(operationType opType) {
		if (opType == operationType.ADD)
			return OperationType.ADD;
		else if (opType == operationType.WITHDRAW)
			return OperationType.WITHDRAW;
		throw new RuntimeException("Type not implemented");
	}

	/**
	 * Read and parses a properties file
	 * @param confName	Properties file name
	 * @return Return the parsed properties
	 * @throws Exception Throws an exception in case of any problem
	 */
	@SuppressWarnings("resource")
	public static Properties readProperties(final String confName) throws Exception {
		BufferedReader br = null;
		InputStreamReader isr = null;
		FileInputStream fis = null;
		Properties properties = new Properties();
		Exception exception = null;

		try {
			fis = new FileInputStream(new File(confName));
			isr = new InputStreamReader(fis);
			br = new BufferedReader(isr);
			String line;
			// Read and parse the file
			while ((line = br.readLine()) != null) {
				Vector<String> tokens = new Vector<String>();
				StringTokenizer st = new StringTokenizer(line, "=");
				while (st.hasMoreTokens())
					tokens.addElement(st.nextToken().trim());
				if (tokens.size() < 2) {
					exception = new Exception("Invalid configuration file: it must contain lines of type \"key = value\"");
					break;
				}
				properties.put(tokens.elementAt(0), tokens.elementAt(1));
				tokens.clear();
			}
		} 
		// Capture exceptions
		catch (FileNotFoundException fnfe) {
			exception = new Exception("Configuration file does not exist: " + confName);
		} catch (IOException ioe) {
			exception = new Exception("Error reading configuration file: " + confName);
		}

		// Close the streams
		if (br != null)
			br.close();
		if (isr != null)
			isr.close();
		if (fis != null)
			fis.close();
		
		if (exception != null)
			throw exception;
		else
			return properties;

	}
}
