#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;
// Timers
unsigned long timer = 0;
float timeStep = 0.01;
int loop_count = 0;

//FFT
//---------------------------------------------------------------------------//
byte sine_data [91]=
 {
0,  
4,    9,    13,   18,   22,   27,   31,   35,   40,   44, 
49,   53,   57,   62,   66,   70,   75,   79,   83,   87, 
91,   96,   100,  104,  108,  112,  116,  120,  124,  127,  
131,  135,  139,  143,  146,  150,  153,  157,  160,  164,  
167,  171,  174,  177,  180,  183,  186,  189,  192,  195,       //Paste this at top of program
198,  201,  204,  206,  209,  211,  214,  216,  219,  221,  
223,  225,  227,  229,  231,  233,  235,  236,  238,  240,  
241,  243,  244,  245,  246,  247,  248,  249,  250,  251,  
252,  253,  253,  254,  254,  254,  255,  255,  255,  255
  };
float f_peaks[5]; // top 5 frequencies peaks in descending order
//---------------------------------------------------------------------------//

// Accelerations
int acc[3][3];
int avg_acc[3];
int old_acc[3];
int d_acc[3];
int d_mag[3];
int avg_d_mag;
int var[3][3];
int avg_var[3];
int var_mag[3];
int avg_var_mag;
int output[255];
int outputSize = 0;
int difficultyLevel = 5;

void setup() 
{
  Serial.begin(115200);

  // Initialize MPU6050
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  
  // Calibrate gyroscope. The calibration must be at rest.
  // If you don't want calibrate, comment this line.
  mpu.calibrateGyro();

  // Set threshold sensivty. Default 3.
  // If you don't want use threshold, comment this line or set 0.
  mpu.setThreshold(3);
}

void loop()
{
  timer = millis();

  calc_acc();
//   show_acc();
  if (loop_count % 100 < 10) {
    digitalWrite(2, HIGH);
  } else {
    digitalWrite(2, LOW);
  }

//   Serial.println("");
  loop_count ++;
  // Wait to full timeStep period
  delay((timeStep*1000) - (millis() - timer));
  FFT(avg_d_mag,LENGTH,100);        //to get top five value of frequencies of X having LENGTH sample at 100Hz sampling
//  Serial.println(f_peaks[0]);
//  Serial.println(f_peaks[1]);
  if (f_peaks[0] > 120 ) {
    difficulty_level_increase();
    }
  if (f_peaks[0] < 50) {
    difficulty_level_decrease();
    }
 Serial.println(["Stability", f_peaks[0]]);
 Serial.println(["Difficulty", difficultyLevel]);
 Serial.println(["Duration", timer]);

}
void difficulty_level_increase(){
  difficultyLevel+=1;
  }
void difficulty_level_decrease(){
  difficultyLevel-=1;
  }
void calc_acc()
{
  Vector rawAccel = mpu.readRawAccel();
  int rawAccel_array[3] = { rawAccel.XAxis, rawAccel.YAxis, rawAccel.ZAxis };
  for (int i=0; i<3; i++) {
    acc[0][i] = acc[1][i];
    acc[1][i] = acc[2][i];
    acc[2][i] = rawAccel_array[i] / 100;
    old_acc[i] = avg_acc[i];
    avg_acc[i] = ( acc[0][i] + acc[1][i] + acc[2][i] ) / 3;
    d_acc[i] = avg_acc[i] - old_acc[i];
  }

  d_mag[0] = d_mag[1];
  d_mag[1] = d_mag[2];
  d_mag[2] = sqrt( d_acc[0]*d_acc[0] + d_acc[1]*d_acc[1] + d_acc[2]*d_acc[2] );
  if (d_mag[2] < 0) {
    d_mag[2] = 32766;
  }
  avg_d_mag = (d_mag[0] + d_mag[1] + d_mag[2]) / 3;
  output[outputSize%255] = avg_d_mag;
  outputSize += 1;

}

void show_acc() {
  Serial.print(" change_in_acceleration:");
  Serial.print(avg_d_mag);
  if (outputSize%255=0) {
    FFT(data, 255, 100);
    Serial.print(" FFT freq. peaks:");
    Serial.print(f_peaks[0] + " " + f_peaks[1] + " " + f_peaks[2] + " " + f_peaks[3] + " " + f_peaks[4]);
  }
}


/*---------------------------------------------------------------------------------------------*/
/*        
void loop() {


//example
FFT(data,64,100);        //to get top five value of frequencies of X having 64 sample at 100Hz sampling
Serial.println(f_peaks[0]);
Serial.println(f_peaks[1]);
delay(99999);
*/


/* 
after ruing above FFT(), frequencies available at f_peaks[0],f_peaks[1],f_peaks[2],f_peaks[3],f_peaks[4],
           
            }
*/


//-----------------------------FFT Function----------------------------------------------//

float FFT(int in[],int N,float Frequency)
{
/*
Code to perform FFT on arduino,
setup:
paste sine_data [91] at top of program [global variable], paste FFT function at end of program
Term:
1. in[]     : Data array, 
2. N        : Number of sample (recommended sample size 2,4,8,16,32,64,128...)
3. Frequency: sampling frequency required as input (Hz)

If sample size is not in power of 2 it will be clipped to lower side of number. 
i.e, for 150 number of samples, code will consider first 128 sample, remaining sample  will be omitted.
For Arduino nano, FFT of more than 128 sample not possible due to mamory limitation (64 recomended)
For higher Number of sample may arise Mamory related issue,
Code by ABHILASH
Contact: abhilashpatel121@gmail.com 
Documentation:https://www.instructables.com/member/abhilash_patel/instructables/
2/3/2021: change data type of N from float to int for >=256 samples
*/

unsigned int data[13]={1,2,4,8,16,32,64,128,256,512,1024,2048};
int a,c1,f,o,x;
a=N;  
                                 
      for(int i=0;i<12;i++)                 //calculating the levels
         { if(data[i]<=a){o=i;} }
      
int in_ps[data[o]]={};     //input for sequencing
float out_r[data[o]]={};   //real part of transform
float out_im[data[o]]={};  //imaginory part of transform
           
x=0;  
      for(int b=0;b<o;b++)                     // bit reversal
         {
          c1=data[b];
          f=data[o]/(c1+c1);
                for(int j=0;j<c1;j++)
                    { 
                     x=x+1;
                     in_ps[x]=in_ps[j]+f;
                    }
         }

 
      for(int i=0;i<data[o];i++)            // update input array as per bit reverse order
         {
          if(in_ps[i]<a)
          {out_r[i]=in[in_ps[i]];}
          if(in_ps[i]>a)
          {out_r[i]=in[in_ps[i]-a];}      
         }


int i10,i11,n1;
float e,c,s,tr,ti;

    for(int i=0;i<o;i++)                                    //fft
    {
     i10=data[i];              // overall values of sine/cosine  :
     i11=data[o]/data[i+1];    // loop with similar sine cosine:
     e=360/data[i+1];
     e=0-e;
     n1=0;

          for(int j=0;j<i10;j++)
          {
          c=cosine(e*j);
          s=sine(e*j);    
          n1=j;
          
                for(int k=0;k<i11;k++)
                 {
                 tr=c*out_r[i10+n1]-s*out_im[i10+n1];
                 ti=s*out_r[i10+n1]+c*out_im[i10+n1];
          
                 out_r[n1+i10]=out_r[n1]-tr;
                 out_r[n1]=out_r[n1]+tr;
          
                 out_im[n1+i10]=out_im[n1]-ti;
                 out_im[n1]=out_im[n1]+ti;          
          
                 n1=n1+i10+i10;
                  }       
             }
     }

/*
for(int i=0;i<data[o];i++)
{
Serial.print(out_r[i]);
Serial.print("\t");                                     // un comment to print RAW o/p    
Serial.print(out_im[i]); Serial.println("i");      
}
*/


//---> here onward out_r contains amplitude and our_in conntains frequency (Hz)
    for(int i=0;i<data[o-1];i++)               // getting amplitude from compex number
        {
         out_r[i]=sqrt(out_r[i]*out_r[i]+out_im[i]*out_im[i]); // to  increase the speed delete sqrt
         out_im[i]=i*Frequency/N;
         /*
         Serial.print(out_im[i]); Serial.print("Hz");
         Serial.print("\t");                            // un comment to print freuency bin    
         Serial.println(out_r[i]); 
         */    
        }




x=0;       // peak detection
   for(int i=1;i<data[o-1]-1;i++)
      {
      if(out_r[i]>out_r[i-1] && out_r[i]>out_r[i+1]) 
      {in_ps[x]=i;    //in_ps array used for storage of peak number
      x=x+1;}    
      }


s=0;
c=0;
    for(int i=0;i<x;i++)             // re arraange as per magnitude
    {
        for(int j=c;j<x;j++)
        {
            if(out_r[in_ps[i]]<out_r[in_ps[j]]) 
                {s=in_ps[i];
                in_ps[i]=in_ps[j];
                in_ps[j]=s;}
        }
    c=c+1;
    }



    for(int i=0;i<5;i++)     // updating f_peak array (global variable)with descending order
    {
    f_peaks[i]=out_im[in_ps[i]];
    }



}
    

float sine(int i)
{
  int j=i;
  float out;
  while(j<0){j=j+360;}
  while(j>360){j=j-360;}
  if(j>-1   && j<91){out= sine_data[j];}
  else if(j>90  && j<181){out= sine_data[180-j];}
  else if(j>180 && j<271){out= -sine_data[j-180];}
  else if(j>270 && j<361){out= -sine_data[360-j];}
  return (out/255);
}

float cosine(int i)
{
  int j=i;
  float out;
  while(j<0){j=j+360;}
  while(j>360){j=j-360;}
  if(j>-1   && j<91){out= sine_data[90-j];}
  else if(j>90  && j<181){out= -sine_data[j-90];}
  else if(j>180 && j<271){out= -sine_data[270-j];}
  else if(j>270 && j<361){out= sine_data[j-270];}
  return (out/255);
}

//------------------------------------------------------------------------------------//
