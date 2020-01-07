package il.co.ilrd.code_review;

public class Product {
	private String name;
	private float price;
	private int maxPerSlot;
	
	public Product(String name, float price, int maxPerSlot){
		this.name = name;
		this.price = price;
		this.maxPerSlot = maxPerSlot;
	}

	public int getMaxPerSlot() {
		return this.maxPerSlot;
	}
	
	public String getName() {
		return name;
	}
	
	public float getPrice() {
		return price;
	}

	public void setPrice(float price) {
		this.price = price;
	}

}
