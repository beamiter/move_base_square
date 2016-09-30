 import java.io.*;
 import java.util.Random;

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
    public static double start[] = {1.0, 1.0, 0};
    public static double end[] = {19.0, 9.0, 0};
    public static int grid[][] = new int[map.cell[1]][map.cell[0]];
    public static int obsthresh = 254;
    public static int insribed_thresh = 253;
    public static int circumscibed_thresh = 128;
    public static double resolution = 0.2;

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
            for (int x=0;x<map.cell[1];x++)
            {
                for (int y=0;y<map.cell[0];y++)
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

    public static void addobs(int a, int b, int c, int d, char flag)
    {
        try{
          Random random = new Random();
            obstacle obs = new obstacle(a, b, c, d);
            // System.out.println("Obstacle info: "+obs.center[0]+"\t"+obs.center[1]+"\t"+obs.width+"\t"+obs.height);
            int xl = obs.center[0]-obs.width/2, xr = obs.center[0]+obs.width/2;
            int yu = obs.center[1]+obs.height/2, yd = obs.center[1]-obs.height/2;

            System.out.println("Obstacle info: "
            +"Left down point: "+xl+","+yd+";\t"
            +"Left up point: "+xl+","+yu+";\t"
            +"Right up point: "+xr+","+yu+";\t"
            +"Right down point: "+xr+","+yd+";\t");
            switch (flag)
            {
              case 'o':
              {
                for (int i=(obs.center[1]-obs.height/2); i< (obs.center[1]+obs.height/2); i++)
                {
                    for (int j=(obs.center[0]-obs.width/2); j<(obs.center[0]+obs.width/2); j++)
                    {
                      map.grid[i][j]=254;
                    }
                }
              }
              break;
              case 'i':
              {
                for (int i=(obs.center[1]-obs.height/2); i< (obs.center[1]+obs.height/2); i++)
                {
                    for (int j=(obs.center[0]-obs.width/2); j<(obs.center[0]+obs.width/2); j++)
                    {
                      map.grid[i][j]=253;
                    }
                }
              }
              break;
              case 'c':
              {
                for (int i=(obs.center[1]-obs.height/2); i< (obs.center[1]+obs.height/2); i++)
                {
                    for (int j=(obs.center[0]-obs.width/2); j<(obs.center[0]+obs.width/2); j++)
                    {
                      map.grid[i][j]=128+random.nextInt(125);
                    }
                }
              }
              break;
              default:
              System.out.println("Waiting for the implementation");
              break;
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
        String s = "discretization(cells):";
        int a[]=new int[2];
        a[0]=map.cell[0];
        a[1]=map.cell[1];
        iarray(fos, s, a);

            s = "obsthresh:";
            iconst(fos,s,map.obsthresh);
            s = "cost_inscribed_thresh:";
            iconst(fos,s,map.insribed_thresh);
            s = "cost_possibly_circumscribed_thresh:";
            iconst(fos,s,map.circumscibed_thresh);
            s = "cellsize(meters):";
            fconst(fos,s,map.resolution);

        s = "nominalvel(mpersecs):";
        fconst(fos,s,1.0);
        s = "timetoturn45degsinplace(secs):";
        fconst(fos,s,2.0);

            s = "start(meters,rads):";
            farray(fos,s,start);
            s = "end(meters,rads):";
            farray(fos,s,end);
            s="environment:";
            strconst(fos, s);

        mapinit();
        char o = 'o';
        char i = 'i';
        char c = 'c';
        addobs(50,25,8,10,c);
        addobs(20,25,8,10,c);
        addobs(75,25,8,10,c);

        addobs(50,10,8,10,c);
        addobs(20,10,8,10,c);
        addobs(75,10,8,10,c);

        addobs(50,40,8,10,o);
        addobs(20,40,8,10,o);
        addobs(75,40,8,10,o);


        mapwrite(fos);

    }
}
