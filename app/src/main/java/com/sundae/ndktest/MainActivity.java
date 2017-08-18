package com.sundae.ndktest;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(stringFromJNI() + "  " + getStringLength("hello"));
        int width = 1000;
        int height = 600;
        Log.e("TAG" , "start");
        int arr[][] = getBitmap(width , height , 0xFF888888);
        Log.e("TAG" , "end");

        int intArr[] = new int[width * height];
        int count = 0;
        for(int i = 0 ; i < width ; i++)
            for (int k = 0 ; k < height ; k++)
                intArr[count++] = arr[i][k];
        Bitmap bitmap = Bitmap.createBitmap(intArr , width , height , Bitmap.Config.ARGB_8888);
        final ImageView imageView = (ImageView) findViewById(R.id.imageView);
        imageView.setImageBitmap(bitmap);


        findViewById(R.id.button).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.e("TAG" , "开始点击");
                Bitmap bitmap1 = BitmapFactory.decodeResource(MainActivity.this.getResources() , R.drawable.pic);
                int w = bitmap1.getWidth();
                int h = bitmap1.getHeight();
                int pixels[] = new int[w*h];

                Log.e("TAG" , "开始转换为int[]");
                int count = 0;
                for(int i = 0 ; i < h ; i++)
                    for (int j = 0 ; j < w ; j++)
                        pixels[count++] = bitmap1.getPixel(j , i);

                Log.e("TAG" , "转换为int[]完成 JNI 灰度化start");
                int p[] = getGrayImage(pixels , w , h);
                Log.e("TAG" , "JNI 灰度化end");
                imageView.setImageBitmap(Bitmap.createBitmap(p , w , h , Bitmap.Config.ARGB_8888));

            }
        });


    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native int getStringLength(String str);

    public native int[][] getBitmap(int width , int height , int color);

    public native int[] getGrayImage(int pixels[] , int width , int height);
}
