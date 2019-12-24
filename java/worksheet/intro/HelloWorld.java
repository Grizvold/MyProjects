
class HelloWorldApp 
{
    private static int i = 0;

    public static void main(String[] args)
    {
        System.out.println("Hello World!"); //Display the string.

        
        recursiveTest(i);
       /*  allocateListOfInt(); */
        
        /* 
        MySecondClass.foo1();
        
        MySecondClass msc1 = new MySecondClass();
        msc1.foo2(); */
    }
    
/*     private static void allocateListOfInt()
    {
        Runtime run_time = Runtime.getRuntime();
    
        ArrayList<int[]> temp_list = new ArrayList<int[]>();
    
        for(int i = 0; i < 1000; ++i)
        {
            long total_memory = run_time.totalMemory();
            long free_memory = run_time.freeMemory();
    
            temp_list.add(new int[100000]);
            System.out.println
            (
                    String.format("#%d, Total: %s, Free: %s, Diff: %s",
                                    i,
                                    total_memory,
                                    free_memory,
                                    total_memory - free_memory)
            );    
        }
    } */

    private static void recursiveTest(int i)
    {
        for(; ;)
        {
            ++i;
            System.out.println(String.format("iterator value: #%d", i));
            recursiveTest(i);
        }
    }
}

