public class JniEx {

    static {
        System.loadLibrary("jniex");
    }

    public static native byte[] incBytes(byte[] bs);

    public static void main(String[] args) {
        byte[] bs = { 1, 2, 3, 4, 5};
        for (int i = 0; i < bs.length; i++) {
            System.out.println(bs[i]);
        }
        byte[] res = incBytes(bs);
        for (int i = 0; i < res.length; i++) {
            System.out.println(res[i]);
        }
    }

}

