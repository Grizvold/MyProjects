package il.co.ilrd.numerics;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * @Author      Ruslan Gorbaty
 * @Reviewer    Shai Roth
 * @Group       FS767
 * @Description Implementation of complex number.
 */

public class Complex implements Comparable <Complex>{
	private double real =  0.0;
	private double imaginary = 0.0;
	private static final Pattern complexNumberPattern = 
						Pattern.compile("(^\\-?[0-9]+[.]{1}?[0-9]+)([-|+]{1}[0-9]+[.]{1}?[0-9]+)i$");

	public Complex() {
		this.real = 0.0;
		this.imaginary = 0.0;
	}
	
	public Complex(double realNumber, double imaginaryNumber) {
		this.real = realNumber;
		this.imaginary = imaginaryNumber;
	}
	
	//Class methods
	public double getReal() {
		return real;
	}
	
	
	public double getImaginary() {	
		return imaginary;
	}
	
	
	public void setReal(double num) {
		real = num;
	}
	
	
	public void setImaginary(double num) {
		imaginary = num;
	}
	
	
	public Complex add(Complex num ) {	
		return new Complex(real + num.real, imaginary + num.imaginary) ;
	}
	
	
	public Complex substract(Complex num ) {	
		return new Complex(real - num.real, imaginary - num.imaginary) ;
	}
	
	
	public boolean isReal() {		
		return (imaginary == 0.0);
	}
	
	
	public boolean isImaginary() {
		return (imaginary != 0.0 && real == 0.0);
	}
	
	
	public static Complex parseString(String  str) {
		double real = 0;
		double imaginary = 0;
		
	    Matcher complexNumberMatcher = complexNumberPattern.matcher(str);

	    if (complexNumberMatcher.find()) { 
	    	real = Double.parseDouble(complexNumberMatcher.group(1)); 
	    	imaginary = Double.parseDouble(complexNumberMatcher.group(2)); 
	    }
	    else {
	    	
			return null;
		}
	    
	    return new Complex(real, imaginary);
	}
	
	@Override
	public int compareTo(Complex complexObject) {
		double thisPow = getSumOfPows(real, imaginary);
		double argPow = getSumOfPows(complexObject.real, complexObject.imaginary);
	    
		return (int)(thisPow - argPow);
	}
	
	private double getSumOfPows(double real, double imaginary)
	{
		return real * real + imaginary * imaginary;
	}
	
	@Override
	public boolean equals(Object complexObject) {
		if(null == complexObject) {
			
			return false;
		}
		
		if (this == complexObject) {
			
			return true;
		}
		
		if (complexObject instanceof Complex) {	
			
			return (Math.abs(real - ((Complex)complexObject).getReal()) < 0.01) 
					&& (Math.abs(imaginary - ((Complex)complexObject).getImaginary()) < 0.01);
		}
		
		return false;
	}
	
	
	@Override
	public int hashCode() {
		int result = 17;
		int prime = 31;
		
		long tempReal = Double.doubleToLongBits(real);
		tempReal = tempReal>>>32;
		long tempImaginary = Double.doubleToLongBits(imaginary);
		tempImaginary = tempImaginary>>>32;
		
		result = prime * result + (int)tempReal;
		result = prime * result + (int)tempImaginary;
		
		return result;
	}	
}
