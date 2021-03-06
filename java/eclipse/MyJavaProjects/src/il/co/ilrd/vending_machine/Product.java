package il.co.ilrd.vending_machine;

/**
 * @Author      Ruslan Gorbaty
 * @Reviewer    Yuval Shlomo
 * @Group       FS767
 * @Description Product implementation. (Used in Vending Machine).
 */

public class Product {
	private String name = null;
	private float price = 0.0f;
	private int maxPerSlot = 0;
	
	public Product(String name, float price, int maxPerSlot){
		this.name = name;
		this.price = price;
		this.maxPerSlot = maxPerSlot;
	}

	public int getMaxPerSlot() {
		return maxPerSlot;
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
