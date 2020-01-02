package il.co.ilrd.numerics;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * @Author      Ruslan Gorbaty
 * @Reviewer    Shai Roth
 * @Group       FS767
 * @Description Implementation of complex number.
 */

public class Complex implements Comparable<Complex>{
	
	private double real;
	private double imaginary;
	
	public Complex () {
		this.real = 0.0;
		this.imaginary = 0.0;
	}
	
	public Complex(double real, double imaginary) {
		this.real = real;
		this.imaginary = imaginary;
	}
	
	public void setReal(double real) {
		this.real = real;
	}

	public void setImaginary(double imaginary) {
		this.imaginary = imaginary;
	}
	
	public double getReal() {
		return real;
	}

	public double getImaginary() {
		return imaginary;
	}

	public boolean isReal() {
		return 0.0 == imaginary;
	}
	
	public boolean isImaginary() {
		return (0.0 != imaginary && 0 == real);
	}

	public Complex add(Complex numComplex) {
		return new Complex(real + numComplex.real, imaginary + numComplex.imaginary);
	}
	
	public Complex substract(Complex numComplex) {
		return new Complex(real - numComplex.real, imaginary - numComplex.imaginary);
	}
	
	public static Complex parseString(String complexString)
	{
		String regex = "(^\\-?[0-9]++[.]{1}[0-9]++)([\\-|\\+]?+[0-9]++[.]{1}[0-9]++)i$";
		Pattern complexPattern = Pattern.compile(regex);
		Matcher complexMatcher = complexPattern.matcher(complexString);
		
		if(!complexMatcher.find())
		{
			return null;
		}
		
		return new Complex(Double.parseDouble(complexMatcher.group(1)),
							Double.parseDouble(complexMatcher.group(2)));
	}
	
	@Override
	public String toString() {
		if(0.0 == imaginary)
		{
			return String.valueOf(real);
		}
		else if(0.0 < imaginary)
		{
			return real + " + " + imaginary + "i";
		}
		else 
		{
			return real + " - " + (imaginary * -1) + "i";
		}
	}
	
	@Override
	public int compareTo(Complex complexnum) {;
		return getComplexPower(this) - getComplexPower(complexnum);
	}

	private double getComplexPower(Complex num1)
	{
		return (num1.real * num1.real + num1.imaginary * num1.imaginary);
	}

	@Override
	public boolean equals(Object complexnum) {
		if(null == complexnum)
		{
			return false;
		}
		if(this == complexnum)
		{
			return true;
		}
		if(complexnum instanceof Complex)
		{
			return (this.real == ((Complex)complexnum).real &&
					this.imaginary == ((Complex)complexnum).imaginary);
		}
		
		return false;
	}
	
	@Override
	public int hashCode() {
		int result = 17;
		int primevalNum = 31;
	
		result = primevalNum * result + this.real;
		result = primevalNum * result + this.imaginary;
		
		return result;
	}
}
