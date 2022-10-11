#include <Wire.h>

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20, 16, 2);

const int buzzer = 8;
const int red = 4;
const int bouton = 9;

int etat_bouton;

// Temps de validation et attente
const int validation = 5000;
const int waiting = 5000;

//bolean attente et mort
bool dead = false;
bool wait = false;

// Mode par défaut
int mode = 0;
// Taut de chance par défaut
int deathChance = 0;
int actualdeathChance =0;
// Etape de soin par défaut
int step = 0;

// Nom des dommages
char Dommage = ' ';

// Appuis sur le bouton
long debut_appuiB;
int healWaiting = 0;



void setup() {
    pinMode(buzzer, OUTPUT);
    pinMode(red, OUTPUT);
    pinMode(bouton, INPUT_PULLUP);
    Serial.begin(9600);
    lcd.init();
    lcd.backlight();
    delay(1000);
    lcd.setCursor(0, 0);
    lcd.print("   TEAM WOLF");
    lcd.setCursor(0, 1);
    lcd.print("    CONCEPT");
    delay(3000);        
}

///////////////////////////////////////
/////////////// Loop //////////////////
///////////////////////////////////////

void loop() {
    if (mode == 1){scan();}
    else {menu();}
}

void scan()
{
    lcd.clear();    
    while(mode == 1)
    {
        etat_bouton = digitalRead(bouton);
        if (etat_bouton == LOW)
        {
            lcd.setCursor(0, 0);
            lcd.print("Scanner en cours");
          	delay(2000);
            randomDommage();
            
        }
    }
}

void randomDommage()
{
  	lcd.clear();
    int ialeatoire = rand () % 5 + 1;
    delay(1000);
    

    switch (ialeatoire){
   case 1 : 
    	Dommage = 'Torse';
    	break;
   case 2 : 
    	Dommage = 'Jambe droite';
    	break;
   case 3 : 
    	Dommage = 'Jambe Gauche';
    	break;
    case 4 : 
    	Dommage = 'Bras Droit';
    	break;    
    default :
    	Dommage = 'Bras Gauche';    	
  }
    scanning();
}

void scanning()
{   
    lcd.setCursor(0,0);
    lcd.print(Dommage);    
    wait = true;
  	// Système de tempo 
    while( wait = true && healWaiting > waiting)
    { 	
       etat_bouton = digitalRead(bouton);
        if (etat_bouton == LOW)
        {
            wait = false;
            healthStep();
        }
    }
    
    if (wait = true && healWaiting <= waiting)
    {
        wait = false;
        death();
    }

}

void deathRandom()
{
    int deathAlea = rand () % 100 + 0;

    if (deathAlea < deathChance && deathChance != 0)
    {
       delay(2000);
       death();
    } else{
        step++;
        delay(2000);
        healthStep();
    }
}

void healthStep()
{
    switch (step){
        case 1:
            lcd.clear();
            lcd.print("step 1");
             deathRandom();
        case 2:
            lcd.clear();
            lcd.print("step 2");
             deathRandom();
        case 3:
            lcd.clear();
            lcd.print("step 3");
             deathRandom();
        case 4:
            lcd.clear();
            lcd.print("step 4");
             deathRandom();
        case 5 :
            lcd.clear();
            lcd.print("Soin termine");             
             step = 0;
             delay(2000);
             scan();
        default : 
             step ++;
             healthStep();
    }
}

void death()
{
    lcd.clear();
    lcd.print("Retour au spawn");
    step = 0;
    delay(2000);
    scan();
}

void menu()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" % de mort = ");
    lcd.setCursor(0, 1);
    lcd.print(deathChance);

    while(mode == 0)
    {
       etat_bouton = digitalRead(bouton);
      
        if (etat_bouton == LOW)
        {          
            debut_appuiB = millis();          	
            submenu();
        }   
    }
}

void submenu()
{  	
  	// Système de durée d'appuis a refaire
    if (deathChance < 100 )
    {
        actualdeathChance = deathChance + 5;
        deathChance = actualdeathChance;
      	
        menu();
    } else if (deathChance == 100)
    {
         actualdeathChance = 0;
         deathChance = actualdeathChance;
         menu();
    }
    //if(debut_appuiB >= validation)
    //{
    //    mode = 1;
    //    scan();
    //}
}