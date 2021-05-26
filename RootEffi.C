// Run in the command line with: grsisort -l RootEffi.C
//
// or with:
//
// grsisort -l
// .x RootEffi.C
//
// Also, the above 'grsisort' can be replaced with 'root' - and it should work just fine!
//

{

// Depending on the information that you have, you can calculate either the absolute or the relative efficiency
// If you are calculating the relative efficiency, you can ignore the following lines about the sources activity :-)

// Calculating the activity of the 152Eu calibration source at the time of the data collection
double euoriginal = 38100.; // Original activity of the source in Bq (decays/s)
double eupastime = 2517.491; // Number of days between the original source activity and the day of the data collection
double euhalflife = 4936.; // Half-life (in days)
double euactivity = euoriginal*TMath::Power(0.5,(eupastime/euhalflife));
//  printf( "\t 152Eu source activity = %.4f Bq \n",euactivity);

// Calculating the number of 152Eu decays during the time of the data collection
double eulivetime = 2010.; // The live time is the difference between the run time and the dead time (in seconds). If you don't know the dead time, use the run time :-)
double eudecays = euactivity*eulivetime;

// You can play with the commented lines to make the code use more than one source at a time :-)
/*
// Calculating the activity of the 60Co calibration source at the time of the data collection
double cooriginal = 38780.; // Original activity of the source in Bq (decays/s)
double copastime = 2517.491; // Number of days between the original source activity and the day of the data collection
double cohalflife = 3135.491; // Half-life (in days)
double coactivity = cooriginal*0.5^(copastime/cohalflife);

// Calculating the number of 60Co decays during the time of the data collection
double colivetime = 2085.; // The live time is the difference between the run time and the dead time (in seconds). If you don't know the dead time, use the run time :-)
double codecays = coactivity*colivetime;;
*/


// Number of transitions that are going to be used for the efficiency calibration
const Int_t n = 9;

// Creating a matrix of n lines for n transitions with all their information (6 values/columns each)
double transition[n][6] {
// 152Eu gamma-ray energy, intensity, intensity uncertainty, area, area uncertainty, and number of decays
   {   121.7817    ,      28.58      ,   0.06    ,   3571261.01    ,   1889.78    ,    eudecays    },
   {   244.6975    ,       7.583     ,   0.019   ,    750817.72    ,    866.50    ,    eudecays    },
//   {   295.9392    ,       0.447       ,   0.005   ,    226894.37    ,    476.33    ,    eudecays    },
   {   344.2785    ,      26.5       ,   0.4     ,   2142110.81    ,   1463.60    ,    eudecays    },
//   {   367.7887    ,       0.861       ,   0.005   ,    226894.37    ,    476.33    ,    eudecays    },
   {   411.1163    ,       2.234     ,   0.004   ,    161541.94    ,    401.92    ,    eudecays    },
// 443 is a doublet  2.821 + 0.327.
   {   443.965     ,       3.148     ,   0.027   ,    226894.37    ,    476.33    ,    eudecays    },
//   {   488.6792    ,       0.419       ,   0.003   ,    226894.37    ,    476.33    ,    eudecays    },
//   {   563.990     ,       0.489       ,   0.006   ,    226894.37    ,    476.33    ,    eudecays    },
//   {   586.2648    ,       0.459       ,   0.005   ,    226894.37    ,    476.33    ,    eudecays    },
//   {   678.623     ,       0.471       ,   0.004   ,    226894.37    ,    476.33    ,    eudecays    },
//   {   688.670     ,       0.857       ,   0.008   ,    226894.37    ,    476.33    ,    eudecays    },
   {   778.9040    ,      12.942     ,   0.019   ,    642933.83    ,    801.83    ,    eudecays    },
   {   867.378     ,       4.245     ,   0.019   ,    200582.85    ,    447.86    ,    eudecays    },
   {   964.079     ,      14.605     ,   0.021   ,    650483.61    ,    806.53    ,    eudecays    },
//   {  1005.272     ,     0.646         ,   0.005   ,    226894.37    ,    476.33    ,    eudecays    },
//   {  1212.948     ,     1.422         ,   0.006   ,    226894.37    ,    476.33    ,    eudecays    },
//   {  1299.140     ,     1.623         ,   0.008   ,    226894.37    ,    476.33    ,    eudecays    },
   {  1408.006     ,      21.005     ,   0.024   ,    753874.87    ,    868.26    ,    eudecays    }};
// 60Co gamma-ray energy, intensity, intensity uncertainty, area, area uncertainty, and number of decays
//   {  1173.237     ,       99.9736     ,   0.0007  ,    226894.37    ,    476.33    ,    codecays    },
//   {  1332.501     ,       99.9856     ,   0.0004  ,    226894.37    ,    476.33    ,    codecays    }};

// Initializing graph to plot the efficiency data 
   TGraphErrors *gr = new TGraphErrors;

// Let's loop through our data (lines and columns) and calculate our efficiency
for(int i =0;i<=n;i++){
      double energy = transition[i][0];
      double intensity = transition[i][1];
      double dintensity = transition[i][2];
      double area = transition[i][3];
      double darea = transition[i][4];
      double decays = transition[i][5];

// Initializing the calculation of the absolute efficiency and its uncertainty 
      double abseffic = 0.0;
      double dabseffic = 0.0;
      abseffic = area/(intensity/100.*decays)*100.;
      dabseffic = abseffic*TMath::Sqrt(TMath::Power((darea/area),2) + TMath::Power((dintensity/intensity),2));

// Initializing the calculation of the relative efficiency and its uncertainty 
      double releffic = 0.0;
      double dreleffic = 0.0;
      releffic = area/intensity/100./100.;
      dreleffic = releffic*TMath::Sqrt(TMath::Power((darea/area),2) + TMath::Power((dintensity/intensity),2));

// Depending on the information that you have, you can calculate either the absolute or the relative efficiency. Choose wisely!
//      gr->SetPoint(i,energy,abseffic);
//      gr->SetPointError(i,0.0,dabseffic);

      gr->SetPoint(i,energy,releffic);
      gr->SetPointError(i,0.0,dreleffic);
      
   }


   gr->Draw("AP");

// Formatting of efficiency graph (optional, but you should still do it!)
//    gr->SetMarkerColor(4);
    gr->SetMarkerStyle(21);
    gr->SetTitle("");

    gr->GetXaxis()->SetTitle("Energy [keV]");
//    gr->GetXaxis()->SetRangeUser(11.4,13.5);
    gr->GetXaxis()->CenterTitle();
    gr->GetXaxis()->SetTitleOffset(1);
    gr->GetXaxis()->SetTitleSize(0.04);
    gr->GetXaxis()->SetLabelSize(0.04);

//    gr->GetYaxis()->SetTitle("Absolute Efficiency [%]");    
    gr->GetYaxis()->SetTitle("Arbitrary Efficiency [%]");
//    gr->GetYaxis()->SetRangeUser(1,2000);
    gr->GetYaxis()->CenterTitle();
    gr->GetYaxis()->SetTitleOffset(1.1);
    gr->GetYaxis()->SetTitleSize(0.04);
    gr->GetYaxis()->SetLabelSize(0.04);
    TGaxis::SetMaxDigits(4);


// Just in case someone is interested, here is the Radware efficiency equation as described at: https://radware.phy.ornl.gov/gf3/gf3.html#5.3.
// However, i haven't been able to get a proper fit with it. The equation from Knoll is below :-)
/*
// Radware efficiency equation
// Setting up the equation to fit
 TF1 *effi_fit = new TF1("effi","exp( (([0]+[1]*log(x/100)+[2]*log(x/100)*log(x/100))**(-[6]) + ([3]+[4]*log(x/1000000)+[5]*log(x/1000000)*log(x/1000000))**(-[6]))**(-1/[6]) )",0,3500);

// Setting up names for the parameters
    effi_fit->SetParName(0,"A");
    effi_fit->SetParName(1,"B");
    effi_fit->SetParName(2,"C");
    effi_fit->SetParName(3,"D");
    effi_fit->SetParName(4,"E");
    effi_fit->SetParName(5,"F");
    effi_fit->SetParName(6,"G");

// Setting up limits/values for the parameters using the SetParLimits(X,X,X), FixParameter(X,X) or SetParameter(X,X) commands
    effi_fit->SetParLimits(0,0,20);
    effi_fit->SetParLimits(1,-2,2);
    effi_fit->FixParameter(2,0);
    effi_fit->SetParLimits(3,0,20);
    effi_fit->SetParLimits(4,-20,20);
    effi_fit->SetParLimits(5,0,20);
    effi_fit->SetParLimits(6,10,30);
*/

// Knoll efficiency equation
// Setting up the equation to fit
 TF1 *effi_fit = new TF1("effi","10**([0] + [1]*log(x) + [2]*log(x)*log(x) + [3]*(x**(-2)))",0,3500);

// Setting up names for the parameters
    effi_fit->SetParName(0,"p0");
    effi_fit->SetParName(1,"p1");
    effi_fit->SetParName(2,"p2");
    effi_fit->SetParName(3,"p3");

// Setting up limits/values for the parameters using the SetParLimits(X,X,X), FixParameter(X,X) or SetParameter(X,X) commands
    effi_fit->SetParLimits(0,-20,20);
    effi_fit->SetParLimits(1,-20,20);
    effi_fit->SetParLimits(2,-20,20);
    effi_fit->SetParLimits(3,-20,20);

    
// Formatting of fit line (optional, but you should still do it!)    
  effi_fit->SetLineColor(kOrange);
  effi_fit->SetNpx(10000);

// Performing the fit!
  gr->Fit(effi_fit, "RME");

// Extracting fit parameters and Chi2 to calculate the reduced Chi2 and print it to the screen
  float p0 = effi_fit->GetParameter(0);
  float p1 = effi_fit->GetParameter(1);
  float p2 = effi_fit->GetParameter(2);
  float p3 = effi_fit->GetParameter(3);
  float chi = effi_fit->GetChisquare()/effi_fit->GetNDF();
  printf( "\t rChi2 = %.4f\n",chi);

  return effi_fit;

// You can add printf statements to print any value to the screen
// The code GRSISort/util/EfficCal.cxx fits the peaks for you! You can also play with that :-)

}
