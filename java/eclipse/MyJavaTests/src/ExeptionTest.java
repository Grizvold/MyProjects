
public class ExeptionTest {

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
