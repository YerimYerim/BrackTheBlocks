package com.example.Blocks;

import androidx.appcompat.app.AppCompatActivity;

import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import com.example.Blocks.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'Blocks' library on application startup.
    static {
        System.loadLibrary("Blocks");
    }

    private ActivityMainBinding binding;
    private View mGLView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
        // Example of a call to a native method
        TextView tv = binding.sampleText;
        tv.setText(stringFromJNI());
        setContentView(R.layout.activity_main);
        mGLView = findViewById(R.id.gl_surfaceView);

    }

    /**
     * A native method that is implemented by the 'Blocks' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}