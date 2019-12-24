class Point
{
    int i = 0;

    
    static void swap(Point point1, Point point2)
    {
        Point temp = new Point();
        temp = point1;
        point1 = point2;
        point2 = temp;
    }
}

class Test
{
    public static void main(String[] args)
    {
        Point p1 = new Point();
        Point p2 = new Point();

        p1.i = 10;
        p2.i = 20;

        /* Point.Add(p1); */
        System.out.println("p1 = " + p1.i + " p2 = " + p2.i);
        Point.swap(p1, p2);
        System.out.println("p1 = " + p1.i + " p2 = " + p2.i);
    }
}

