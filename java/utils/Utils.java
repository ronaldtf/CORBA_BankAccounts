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

import account.OperationDelegate.OperationType;

public class Utils {

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
	
	public static OperationType convertType(operationType opType) {
		if (opType == operationType.ADD)
			return OperationType.ADD;
		else if (opType == operationType.WITHDRAW)
			return OperationType.WITHDRAW;
		throw new RuntimeException("Type not implemented");
	}

	@SuppressWarnings("resource")
	public static Properties readProperties(final String confName) throws Exception {
		BufferedReader br = null;
		InputStreamReader isr = null;
		FileInputStream fis = null;
		try {
			Properties properties = new Properties();
			fis = new FileInputStream(new File(confName));
			isr = new InputStreamReader(fis);
			br = new BufferedReader(isr);
			String line;
			while ((line = br.readLine()) != null) {
				Vector<String> tokens = new Vector<String>();
				StringTokenizer st = new StringTokenizer(line, "=");
				while (st.hasMoreTokens())
					tokens.addElement(st.nextToken().trim());
				if (tokens.size() < 2)
					throw new Exception("Invalid configuration file: it must contain lines of type \"key = value\"");
				properties.put(tokens.elementAt(0), tokens.elementAt(1));
				tokens.clear();
			}
			br.close();
			isr.close();
			fis.close();
			return properties;
		} catch (FileNotFoundException fnfe) {
			if (br != null)
				br.close();
			if (isr != null)
				isr.close();
			if (fis != null)
				fis.close();
			throw new Exception("Configuration file does not exist: " + confName);
		} catch (IOException ioe) {
			if (br != null)
				br.close();
			if (isr != null)
				isr.close();
			if (fis != null)
				fis.close();
			throw new Exception("Error reading configuration file: " + confName);
		}
	}
}
