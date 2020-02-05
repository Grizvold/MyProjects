import java.util.function.Consumer;

public class MethodReferenceTest {

	public static void main(String[] args) {
		Consumer<String> c = s -> System.out.println(s);
		Consumer<String> d = System.out::println;
		System.out.println(c);
		System.out.println(d);
	}

	public static void staticMethod(String arg) {
		System.out.println(arg);
	}
}

interface StaticInterface{
	void staticMethod(String arg);
}