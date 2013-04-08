public class JniEx {

    static {
        System.loadLibrary("jniex");
    }

    public native byte[] incBytes(byte[] bs);

    public static void main(String[] args) {
        JniEx ex = new JniEx();
        Thread t1 = new Thread(new JniExThread(ex));
        Thread t2 = new Thread(new JniExThread(ex));
        t1.start();
        t2.start();
    }

}

class JniExThread implements Runnable {

    JniEx jniex;

    public JniExThread(JniEx ex) {
       jniex = ex; 
    }

    public void run() {
        byte[] bs = { 1, 2, 3, 4, 5};
        for (int i = 0; i < bs.length; i++) {
            System.out.println(bs[i]);
        }
        byte[] res = jniex.incBytes(bs);
        for (int i = 0; i < res.length; i++) {
            System.out.println(res[i]);
        }
    }

}

