 import java.io.*;

/**
 * 使用FileOutputStream写文件示例
 */

class obstacle{
    int width, height, size;
    int[] center = new int[2]; 
    public obstacle(int a, int b, int c, int d){
        this.center[0] = a;
        this.center[1] = b;
        this.width = c;
        this.height = d;
        System.out.println("Allocation succeeded!!!");
    }
    public int area()
    {
        this.size = this.width*this.height;
        System.out.println("Obstacle size is: "+this.size);
        return this.size;
    }
}

public class map <T>{
    public static final String name = "map.cfg";
    public static int cell[] = {100,50};
    public static double start[] = {1.0, 1.0, 0.0};
    public static double end[] = {24.0, 11.0, 0.0};
    public static int grid[][] = new int[map.cell[0]][map.cell[1]];

    public static void fileinit()
    {
        File file = new File(map.name);
        if (!file.exists())
        {
            try{
                file.createNewFile();
            }catch (Exception e){
                e.printStackTrace();
            }
        }
        else
        {
            System.out.println("File exists!!!");
        }
    }

    public static void mapinit()
    {
        try{
            for (int x=0;x<map.cell[0];x++)
            {
                for (int y=0;y<map.cell[1];y++)
                {
                    map.grid[x][y]=0;
                }
            }
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    public static void mapwrite(FileOutputStream fos)
    {
        int num;
        try{
            //转换为byte数组
            byte[] lines = "\n".getBytes();
            byte[] tabs = " ".getBytes();
            byte[] data;
            for (int x=0;x<map.grid.length;x++)
            {
                for (int y=0;y<map.grid[x].length;y++)
                {
                    num = map.grid[x][y];
                    data = String.valueOf(num).getBytes();
                    fos.write(data);
                    fos.write(tabs);
                }
                fos.write(lines);
            }
            fos.write(lines);
        }catch (Exception e) {
        e.printStackTrace();
    }
    }

    public static void addobs(int a, int b, int c, int d)
    {
        try{
            obstacle obs = new obstacle(a, b, c, d);
            System.out.println("Obstacle info: "+obs.center[0]+"\t"+obs.center[1]+"\t"+obs.height+"\t"+obs.width);
        for (int i=(obs.center[0]-obs.height); i< (obs.center[0]+obs.height); i++)
        {
            for (int j=(obs.center[1]-obs.width); j<(obs.center[1]+obs.width); j++)
            {
                map.grid[i][j]=1;
                // System.out.println("x coordinate and y coordinate are: "+i+"\t"+j);
            }

        }

        }catch (Exception e) {
            e.printStackTrace();
        }

    }

    public static FileOutputStream fosinit(String s)
    {
        FileOutputStream fos = null;
        try{
            fos = new FileOutputStream(s);
        }catch (Exception e) {
        e.printStackTrace();
    }
    return fos;     
    }

    public static void fosclose(FileOutputStream fos)
    {
    try{
        fos.close();
    }catch(Exception e){
        e.printStackTrace();
    }     
    }

    public static void iconst(FileOutputStream fos, String str, final int a)
    {
        try{
            //转换为byte数组
            byte[] lines = "\n".getBytes();
            byte[] tabs = " ".getBytes();
            byte[] data;
            byte[] head = str.getBytes();
            fos.write(head);
            fos.write(tabs);
            data = String.valueOf(a).getBytes();
            fos.write(data);
            fos.write(lines);
        }catch (Exception e) {
        e.printStackTrace();
    }
    }

    public static void fconst(FileOutputStream fos, String str, final double a)
    {
        try{
            //转换为byte数组
            byte[] lines = "\n".getBytes();
            byte[] tabs = " ".getBytes();
            byte[] data;
            byte[] head = str.getBytes();
            fos.write(head);
            fos.write(tabs);
            data = String.valueOf(a).getBytes();
            fos.write(data);
            fos.write(lines);
        }catch (Exception e) {
        e.printStackTrace();
    }
    }

    public static void iarray(FileOutputStream fos, String str, int array[])
    {
        int num = 0;  
        try{
            //转换为byte数组
            byte[] lines = "\n".getBytes();
            byte[] tabs = " ".getBytes();
            byte[] data;
            byte[] head = str.getBytes();
            fos.write(head);
            fos.write(tabs);
            for(int i=0; i<array.length; i++)
            {
                num = array[i];
                data = String.valueOf(num).getBytes();
                fos.write(data);
                fos.write(tabs);
            }
            fos.write(lines);
        }catch (Exception e) {
        e.printStackTrace();
    }
    }

    public static void farray(FileOutputStream fos, String str, double array[])
    {
        double num = 0;
        try{
            //转换为byte数组
            byte[] lines = "\n".getBytes();
            byte[] tabs = " ".getBytes();
            byte[] data;
            byte[] head = str.getBytes();
            fos.write(head);
            fos.write(tabs);
            for(int i=0; i<array.length; i++)
            {
                num = array[i];
                data = String.valueOf(num).getBytes();
                fos.write(data);
                fos.write(tabs);
            }
            fos.write(lines);
        }catch (Exception e) {
        e.printStackTrace();
    }
    }

    public static void strconst(FileOutputStream fos, String str)
    {
        try{
            //转换为byte数组
            byte[] lines = "\n".getBytes();
            byte[] tabs = " ".getBytes();
            byte[] head = str.getBytes();
            fos.write(head);
            fos.write(lines);
        }catch (Exception e) {
        e.printStackTrace();
    }
    }

    public static void main(String[] args) {
        FileOutputStream fos = fosinit(map.name);
        // obstacle obs = new obstacle(1,2,3,4);
        String s = "discretization(cells):";
        int a[]=new int[2];
        a[0]=map.cell[0];
        a[1]=map.cell[1];
        iarray(fos, s, a);
        s = "obsthresh:";
        iconst(fos,s,1);
        s = "cost_inscribed_thresh:";
        iconst(fos,s,1);
        s = "cost_possibly_circumscribed_thresh:";
        iconst(fos,s,0);
        s = "cellsize(meters):";
        fconst(fos,s,0.25);
        s = "nominalvel(mpersecs):";
        fconst(fos,s,1.0);
        s = "timetoturn45degsinplace(secs):";
        fconst(fos,s,1.0);
        s = "start(meters,rads):";
        farray(fos,s,start);
        s = "end(meters,rads):";
        farray(fos,s,end);
        s="environment:";
        strconst(fos, s);

        mapinit();
        addobs(50,25,5,6);
        addobs(25,25,5,6);
        addobs(75,25,5,6);
        mapwrite(fos);

    }
}