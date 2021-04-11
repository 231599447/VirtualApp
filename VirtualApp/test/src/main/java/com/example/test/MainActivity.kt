package com.example.test

import android.content.Context
import android.os.Binder
import android.os.Bundle
import android.os.Environment
import android.support.v7.app.AppCompatActivity
import android.util.Log
import com.blankj.utilcode.util.FileIOUtils
import com.example.test.R
import java.io.File
import java.lang.Exception

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        logd( "test UID = " + Binder.getCallingUid())
        logd( "/sys/class/net/wifi/address = " + FileIOUtils.readFile2String(File("/sys/class/net/wifi/address")))

        logd("onCreate cacheDir: $cacheDir")
        val testFile = File("$cacheDir/test");
        testFile.createNewFile()


        logd("onCreate externalCacheDir: $externalCacheDir")

        val sdDir = Environment.getExternalStorageDirectory();//获取跟目录
        logd("onCreate sdDir: $sdDir")

        //无法访问
        try {
            val dataFile = File("/data/data/"+packageName+"/test.data");
            dataFile.createNewFile()
        }catch (e:Exception){

        }


        //虚拟app可以访问此目录
        try {
            val dataFile = File("/data/user/0/io.busniess.va/test.data");
            dataFile.createNewFile()
        }catch (e:Exception){
        }


        val sharedPreference =  getSharedPreferences("PREFERENCE_NAME", Context.MODE_PRIVATE)
        var editor = sharedPreference.edit()
        editor.putString("username","Anupam")
        editor.putLong("l",100L)
        editor.apply()

    }


    fun logd(msg: String){
        Log.d("xyh", msg)
    }
}