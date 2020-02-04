package il.co.ilrd.design_pattern.singleton;

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
