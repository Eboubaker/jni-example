package bot;
import java.io.IOException;

public class Decompress {
	static{
		System.loadLibrary("Decompress.dll");
	}
	public static native byte[] bytes(byte[] bytes, int dataSize, int expectedSize) throws IOException;
}
