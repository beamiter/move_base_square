 import java.io.*;
 import java.util.Random;
 import java.util.Arrays;

/**
 * 使用FileOutputStream写文件示例
 */
class triangle{
    int[] top = new int[2];
    int[] left = new int[2];
    int[] right = new int[2];
    public triangle(int a, int b, int c, int d, int e, int f){
      this.top[0] = a;
      this.top[1] = b;
      this.left[0] = c;
      this.left[1] = d;
      this.right[0] = e;
      this.right[1] = f;
      System.out.println("Triangle initilized!");
    }
}

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

public class map{
    public static final String name = "map.cfg";
    public static final String obsname = "obstacles.cfg";
    public static final String triname = "triangle.cfg";
    public static int cell[] = {50,100};
    public static float start[] = {(float)2.0, (float)5.0, (float)0.0};
    public static float end[] = {(float)18.0, (float)5.0, (float)0.0};
    public static int grid[][] = new int[map.cell[0]][map.cell[1]];
    public static int obsthresh = 254;
    public static int insribed_thresh = 253;
    public static int circumscibed_thresh = 128;
    public static float resolution = (float)0.1;

    public static void fileinit(String str)
    {
        File file = new File(str);
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
            for (int a=0;a<map.grid.length;a++)
            {
                for (int b=0;b<map.grid[a].length;b++)
                {
                  num = map.grid[a][b];
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

    public static void obsinit(FileOutputStream obsf){
      try{
         //转换为byte数组
         // String str = "Obstacle info:";
         // byte[] lines = "\n".getBytes();
         // byte[] tabs = " ".getBytes();
         // byte[] head = str.getBytes();
         // obsf.write(head);
         // obsf.write(lines);
         // str = "Left down point: ";
         // head = str.getBytes();
         // obsf.write(head);
         // obsf.write(tabs);
         // str = "Left up point: ";
         // head = str.getBytes();
         // obsf.write(head);
         // obsf.write(tabs);
         // str = "Right up point: ";
         // head = str.getBytes();
         // obsf.write(head);
         // obsf.write(tabs);
         // str = "Right down point: ";
         // head = str.getBytes();
         // obsf.write(head);
         // obsf.write(lines);
        PrintStream p = new PrintStream(obsf);
        p.println("Obstacle info:\n"+"Left down point:\t"+"Left up point:\t    "
                  +"Right up point:\t    "+"Right down point:");
      } catch (Exception e){
        e.printStackTrace();
      }
    }

    public static void triinit(FileOutputStream obsf){
      try{
         //转换为byte数组
         // String str = "Obstacle info:";
         // byte[] lines = "\n".getBytes();
         // byte[] tabs = " ".getBytes();
         // byte[] head = str.getBytes();
         // obsf.write(head);
         // obsf.write(lines);
         // str = "Top point:";
         // head = str.getBytes();
         // obsf.write(head);
         // obsf.write(tabs); 
         // obsf.write(tabs);
         // str = "Left point:";
         // head = str.getBytes();
         // obsf.write(head);
         // obsf.write(tabs); 
         // obsf.write(tabs);
         // str = "RightTop point:";
         // head = str.getBytes();
         // obsf.write(head);
         // obsf.write(lines); 
        PrintStream p = new PrintStream(obsf);
        p.println("Obstacle info:\n"+"Top point:\t"
                  +"Left point:\t"+"RightTop point:");
      } catch (Exception e){
        e.printStackTrace();
      }
    }

    public static void writeobs(FileOutputStream obsf, float x[]){
      try {
          int i = x.length;
            //转换为byte数组
            // byte[] lines = "\n".getBytes();
            // byte[] tabs = " ".getBytes();
            // byte[] comma = ",".getBytes();
            // byte[] data;
          if (i == 4){
            PrintStream p = new PrintStream(obsf);
            p.println(x[0]+", \t"+x[3]+"; \t\t"+
                      x[0]+", \t"+x[2]+"; \t\t"+
                      x[1]+", \t"+x[2]+"; \t\t"+
                      x[1]+", \t"+x[3]+"; \t\t");
            // data = String.valueOf(x[0]).getBytes();
            // obsf.write(data);           
            // obsf.write(comma);
            // obsf.write(comma);
            // data = String.valueOf(x[3]).getBytes();
            // obsf.write(data);           
            // obsf.write(tabs);
            // obsf.write(tabs);
            // data = String.valueOf(x[0]).getBytes();
            // obsf.write(data);           
            // obsf.write(comma);
            // obsf.write(comma);
            // data = String.valueOf(x[2]).getBytes();
            // obsf.write(data);           
            // obsf.write(tabs);
            // obsf.write(tabs);
            // data = String.valueOf(x[1]).getBytes();
            // obsf.write(data);           
            // obsf.write(comma);
            // obsf.write(comma);
            // data = String.valueOf(x[2]).getBytes();
            // obsf.write(data);           
            // obsf.write(tabs);
            // obsf.write(tabs);
            // data = String.valueOf(x[1]).getBytes();
            // obsf.write(data);           
            // obsf.write(comma);
            // obsf.write(comma);
            // data = String.valueOf(x[3]).getBytes();
            // obsf.write(data);           
            // obsf.write(tabs);
            // obsf.write(tabs);
            // obsf.write(lines);
          }
          else if(i ==6){
            PrintStream p = new PrintStream(obsf);
            p.println(x[0]+", "+x[1]+"; \t"+
                      x[2]+", "+x[3]+"; \t"+
                      x[4]+", "+x[5]+"; \t");
            // data = String.valueOf(x[0]).getBytes();
            // obsf.write(data);           
            // obsf.write(comma);
            // data = String.valueOf(x[1]).getBytes();
            // obsf.write(data);           
            // obsf.write(tabs);
            // obsf.write(tabs);
            // data = String.valueOf(x[2]).getBytes();
            // obsf.write(data);           
            // obsf.write(comma);
            // data = String.valueOf(x[3]).getBytes();
            // obsf.write(data);           
            // obsf.write(tabs);
            // obsf.write(tabs);
            // data = String.valueOf(x[4]).getBytes();
            // obsf.write(data);           
            // obsf.write(comma);
            // data = String.valueOf(x[5]).getBytes();
            // obsf.write(data);           
            // obsf.write(tabs);
            // obsf.write(tabs);
            // obsf.write(lines);
          }
      } catch (Exception e){
          e.printStackTrace();
      }
    }

    public static float f(int x, int y, int m, int n, float k)
    {
      return (float)(y-n-k*(x-m));
    }

    public static void addtri(FileOutputStream obsf, int a, int b, int c, int d, int e, int f, char flag)
    {
      try{
        Random random = new Random();
        triangle tri = new triangle(a , b, c, d, e, f);
        float[] array = new float[6];
        int[] xarr = new int[3];
        int[] yarr = new int[3];
        array[0] = xarr[0] = a;
        array[1] = yarr[0] = b;
        array[2] = xarr[1] = c;
        array[3] = yarr[1] = d;
        array[4] = xarr[2] = e;
        array[5] = yarr[2] = f;
        Arrays.sort(xarr);
        Arrays.sort(yarr);
        array[0] = array[0]*map.resolution;
        array[1] = array[1]*map.resolution;
        array[2] = array[2]*map.resolution;
        array[3] = array[3]*map.resolution;
        array[4] = array[4]*map.resolution;
        array[5] = array[5]*map.resolution;
        writeobs(obsf, array);
        float k1 = (float)(b-d)/(a-c);
        float k2 = (float)(b-f)/(a-e);
        float k3 = (float)(d-f)/(c-e);
        System.out.println(k1+", "+k2+", "+k3+";");
        switch (flag){
          case 'o':
          {
            for (int i = yarr[0]; i< yarr[2]; i++)
            {
              for (int j = xarr[0]; j <xarr[2]; j++)
              {
                if ( f(j,i,c,d,k1)*f(e,f,c,d,k1)>=0 && f(j,i,a,b,k2)*f(c,d,a,b,k2)>=0 && f(j,i,e,f,k3)*f(a,b,e,f,k3)>=0)
                {
                  map.grid[i][j] = 254;
                }
              }
            }
          }
          break;
          case 'i':
          {
            for (int i = yarr[0]; i< yarr[2]; i++)
            {
              for (int j = xarr[0]; j <xarr[2]; j++)
              {
                if ( f(j,i,c,d,k1)*f(e,f,c,d,k1)>=0 && f(j,i,a,b,k2)*f(c,d,a,b,k2)>=0 && f(j,i,e,f,k3)*f(a,b,e,f,k3)>=0)
                {
                  map.grid[i][j] = 253;
                }
              }
            }
          }
          break;
          case 'c':
          {
            for (int i = yarr[0]; i< yarr[2]; i++)
            {
              for (int j = xarr[0]; j <xarr[2]; j++)
              {
                if ( f(j,i,c,d,k1)*f(e,f,c,d,k1)>=0 && f(j,i,a,b,k2)*f(c,d,a,b,k2)>=0 && f(j,i,e,f,k3)*f(a,b,e,f,k3)>=0)
                {
                  map.grid[i][j]=128+random.nextInt(125);
                }
              }
            }
          }
          break;
          default:
          System.out.println("Waiting for the implementation");
          break;
        }
      } catch (Exception err){
        err.printStackTrace();
      }
    }

    public static void addobs(FileOutputStream obsf, int a, int b, int c, int d, char flag)
    {
        try{
          Random random = new Random();
            obstacle obs = new obstacle(a, b, c, d);
            float xl = obs.center[0]-obs.width/2, xr = obs.center[0]+obs.width/2;
            float yu = obs.center[1]+obs.height/2, yd = obs.center[1]-obs.height/2;
            float[] array = new float[4];
            array[0] = xl*map.resolution;
            array[1] = xr*map.resolution;
            array[2] = yu*map.resolution;
            array[3] = yd*map.resolution;
            writeobs(obsf, array);

            // System.out.println("Obstacle info: \n"
            // +"Left down point: "+xl+","+yd+";\t"
            // +"Left up point: "+xl+","+yu+";\t"
            // +"Right up point: "+xr+","+yu+";\t"
            // +"Right down point: "+xr+","+yd+";\t");
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
            // byte[] lines = "\n".getBytes();
            // byte[] tabs = " ".getBytes();
            // byte[] data;
            // byte[] head = str.getBytes();
            // fos.write(head);
            // fos.write(tabs);
            // data = String.valueOf(a).getBytes();
            // fos.write(data);
            // fos.write(lines);
          PrintStream p = new PrintStream(fos);
          p.println(str+" "+a);
        }catch (Exception e) {
        e.printStackTrace();
    }
    }

    public static void fconst(FileOutputStream fos, String str, final float a)
    {
        try{
            //转换为byte数组
            // byte[] lines = "\n".getBytes();
            // byte[] tabs = " ".getBytes();
            // byte[] data;
            // byte[] head = str.getBytes();
            // fos.write(head);
            // fos.write(tabs);
            // data = String.valueOf(a).getBytes();
            // fos.write(data);
            // fos.write(lines);
          PrintStream p = new PrintStream(fos);
          p.println(str+" "+a);
        }catch (Exception e) {
        e.printStackTrace();
    }
    }

    public static void iarray(FileOutputStream fos, String str, int array[])
    {
        int num = 0;
        try{
            // 转换为byte数组
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

    public static void farray(FileOutputStream fos, String str, float array[])
    {
        float num = 0;
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
            // byte[] lines = "\n".getBytes();
            // byte[] tabs = " ".getBytes();
            // byte[] head = str.getBytes();
            // fos.write(head);
            // fos.write(lines);
          PrintStream p = new PrintStream(fos);
          p.println(str);
        }catch (Exception e) {
        e.printStackTrace();
      }
    }

    public static void main(String[] args) {
        FileOutputStream fos = fosinit(map.name);
        FileOutputStream obsf = fosinit(map.obsname);
        FileOutputStream trif = fosinit(map.triname);
        obsinit(obsf);
        triinit(trif);
        String s = "discretization(cells):";
        int a[] =new int[2];
        float nominalvel = (float)1.0;
        float timeinplace = (float)2.0;
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
        fconst(fos,s,nominalvel);
        s = "timetoturn45degsinplace(secs):";
        fconst(fos,s,timeinplace);

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

        addobs(obsf,50,25,8,10,c);
        // addobs(obsf,20,25,8,10,o);
        // addobs(obsf,75,25,8,10,o);

        // addobs(obsf,50,30,16,25,c);
        // addobs(obsf,20,30,16,25,c);
        // addobs(obsf,75,30,16,25,c);
        
        // addobs(obsf,50,40,8,10,c);
        // addobs(obsf,20,40,8,10,c);
        // addobs(obsf,75,40,8,10,c);

        // addtri(trif,75,25,65,5,85,15,o);
        addtri(trif,55,35,45,15,65,25,c);
        // addtri(trif,35,45,25,25,45,35,o);

        mapwrite(fos);
        fosclose(fos);
        fosclose(obsf);
        fosclose(trif);
    }
}
