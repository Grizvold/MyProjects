package il.co.ilrd.design_pattern;

public enum EnumSingleton {
	INSTANCE;

	private int value;
	
	public int getValue() {
		return value;
	}
	
	/* initialized only once */
	public void setValue(int value) {
		this.value = value;
	}
}
