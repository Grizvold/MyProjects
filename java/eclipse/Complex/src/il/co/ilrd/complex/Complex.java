package il.co.ilrd.complex;

import java.util.Comparator;
import java.util.Objects;

@SuppressWarnings("unused")

public class Complex implements Comparable<Complex>{
	
	private double real;
	private double imaginary;
	
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
		return 0 == this.imaginary;
	}
	
	public boolean isImaginary() {
		return (0 != this.imaginary && 0 == this.real);
	}

	public Complex add(double num) {
		return new Complex(this.real + num, imaginary);
	}
	
	public Complex add(Complex numComplex) {
		return new Complex(this.real + numComplex.real, this.imaginary + numComplex.imaginary);
	}
	
	public Complex substract(double num) {
		return new Complex(this.real - num, imaginary);
	}
	
	public Complex substract(Complex numComplex) {
		return new Complex(this.real - numComplex.real, this.imaginary - numComplex.imaginary);
	}
	
	@Override
	public String toString() {
		if(0 == imaginary)
		{
			return String.valueOf(real);
		}
		else if(0 < imaginary)
		{
			return real + " + " + imaginary + "i";
		}
		else 
		{
			return real + " + " + -imaginary + "i";
		}
	}
	
	@Override
	public int compareTo(Complex o) {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public boolean equals(Object obj) {
		// TODO Auto-generated method stub
		return super.equals(obj);
	}
	
	@Override
	public int hashCode() {
		// TODO Auto-generated method stub
		return super.hashCode();
	}
}
