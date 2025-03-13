package com.sharknade.apks

import android.os.Bundle
import android.util.Log
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import com.sharknade.apks.hook.Shark
import com.sharknade.apks.ui.theme.ApksTheme
import com.sharknade.native_lib.NativeLib

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            ApksTheme {
                Scaffold(modifier = Modifier.fillMaxSize()) { innerPadding ->
                    Column {
                        Greeting(
                            name = "Original Call for Eat",
                            modifier = Modifier
                                .padding(innerPadding)
                                .clickable {
                                    Shark.eat()

                                }
                        )
                        Greeting(
                            name = "doHook",
                            modifier = Modifier
                                .padding(innerPadding)
                                .clickable {
                                    Log.e("shark", NativeLib().stringFromJNI(Shark))
                                }
                        )

                        Greeting(
                            name = "call again",
                            modifier = Modifier
                                .padding(innerPadding)
                                .clickable {
                                    Shark.eat()
                                }
                        )
                    }

                }
            }
        }
    }
}

@Composable
fun Greeting(name: String, modifier: Modifier = Modifier) {
    Text(
        text = "Hello $name!",
        modifier = modifier
    )
}

@Preview(showBackground = true)
@Composable
fun GreetingPreview() {
    ApksTheme {
        Greeting("Android")
    }
}