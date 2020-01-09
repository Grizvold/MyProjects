package il.co.ilrd.inner_classes;

public class InnerClassesTest {

   public int x = 0;

    class FirstLevel {

        public int x = 1;

        void methodInFirstLevel(int x) {
            System.out.println("x = " + x);
            System.out.println("this.x = " + this.x);
            System.out.println("ShadowTest.this.x = " + InnerClassesTest.this.x);
        }
    }

    public static void main(String... args) {
    	InnerClassesTest st = new InnerClassesTest();
    	InnerClassesTest.FirstLevel fl = st.new FirstLevel();
        fl.methodInFirstLevel(23);
    }
}