
public class ExeptionTest {

	@SuppressWarnings("unused")
	public static void main(String[] args) {
		try {
			Thread thread = new Thread(new Runnable() {
				
				@Override
				public void run() {
					throw new RuntimeException();
					
				}
			});
		} catch (Exception e) {
			System.out.println("*******************************");
		}
	}

}
