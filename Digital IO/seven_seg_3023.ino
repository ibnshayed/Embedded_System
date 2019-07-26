//seven_seg_3023.ino


const unsigned char a = 0;
const unsigned char b = 1;
const unsigned char c = 2;
const unsigned char d = 3;
const unsigned char e = 4;
const unsigned char f = 5;
const unsigned char g = 6;

void setup() {
  // put your setup code here, to run once:
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);

  digitalWrite(a, 0);
  digitalWrite(b, 0);
  digitalWrite(c, 0);
  digitalWrite(d, 0);
  digitalWrite(e, 0);
  digitalWrite(f, 0);
  digitalWrite(g, 0);

}



void loop() {
  // put your main code here, to run repeatedly:
  unsigned char i;
  for(i=0;i<15;i++)
  {
  	display_digit(i);
  	delay(1000);
  }
}

void display_digit(unsigned char digit)
{
	switch (digit) {
	    case 0:
	      // 0 -> 	0 1 1 1 1 1 1
	      digitalWrite(a, 1);
	      digitalWrite(b, 1);
	      digitalWrite(c, 1);
	      digitalWrite(d, 1);
	      digitalWrite(e, 1);
	      digitalWrite(f, 1);
	      digitalWrite(g, 0);
	      break;
	    case 1:
	      // 1 ->	0 0 0 0 1 1 0
	      digitalWrite(a, 0);
	      digitalWrite(b, 1);
	      digitalWrite(c, 1);
	      digitalWrite(d, 0);
	      digitalWrite(e, 0);
	      digitalWrite(f, 0);
	      digitalWrite(g, 0);
	      break;
	    case 2:
	      // 2 ->	1 0 1 1 0 1 1
	      digitalWrite(a, 1);
	      digitalWrite(b, 1);
	      digitalWrite(c, 0);
	      digitalWrite(d, 1);
	      digitalWrite(e, 1);
	      digitalWrite(f, 0);
	      digitalWrite(g, 1);
	      break;
	    case 3:
	      // 3 ->	1 0 0 1 1 1 1
	      digitalWrite(a, 1);
	      digitalWrite(b, 1);
	      digitalWrite(c, 1);
	      digitalWrite(d, 1);
	      digitalWrite(e, 0);
	      digitalWrite(f, 0);
	      digitalWrite(g, 1);
	      break;
	    case 4:
	      // 4 ->	1 1 0 0 1 1 0
	      digitalWrite(a, 0);
	      digitalWrite(b, 1);
	      digitalWrite(c, 1);
	      digitalWrite(d, 0);
	      digitalWrite(e, 0);
	      digitalWrite(f, 1);
	      digitalWrite(g, 1);
	      break;
	    case 5:
	      // 5 ->	1 1 0 1 1 0 1
	      digitalWrite(a, 1);
	      digitalWrite(b, 0);
	      digitalWrite(c, 1);
	      digitalWrite(d, 1);
	      digitalWrite(e, 0);
	      digitalWrite(f, 1);
	      digitalWrite(g, 1);
	      break;
	    case 6:
	      // 6 ->	1 1 1 1 1 0 1
	      digitalWrite(a, 1);
	      digitalWrite(b, 0);
	      digitalWrite(c, 1);
	      digitalWrite(d, 1);
	      digitalWrite(e, 1);
	      digitalWrite(f, 1);
	      digitalWrite(g, 1);
	      break;
	    case 7:
	      // 7 ->	0 0 0 0 1 1 1
	      digitalWrite(a, 1);
	      digitalWrite(b, 1);
	      digitalWrite(c, 1);
	      digitalWrite(d, 0);
	      digitalWrite(e, 0);
	      digitalWrite(f, 0);
	      digitalWrite(g, 0);
	      break;
	    case 8:
	      // 8 ->	1 1 1 1 1 1 1
	      digitalWrite(a, 1);
	      digitalWrite(b, 1);
	      digitalWrite(c, 1);
	      digitalWrite(d, 1);
	      digitalWrite(e, 1);
	      digitalWrite(f, 1);
	      digitalWrite(g, 1);
	      break;
	    case 9:
	      // 9 ->	1 1 0 1 1 1 1
	      digitalWrite(a, 1);
	      digitalWrite(b, 1);
	      digitalWrite(c, 1);
	      digitalWrite(d, 1);
	      digitalWrite(e, 0);
	      digitalWrite(f, 1);
	      digitalWrite(g, 1);
	      break;
	    case 10:
	      // A ->	1 1 1 0 1 1 1
	      digitalWrite(a, 1);
	      digitalWrite(b, 1);
	      digitalWrite(c, 1);
	      digitalWrite(d, 0);
	      digitalWrite(e, 1);
	      digitalWrite(f, 1);
	      digitalWrite(g, 1);
	      break;
	    case 11:
	      // b ->	1 1 1 1 1 0 0
	      digitalWrite(a, 0);
	      digitalWrite(b, 0);
	      digitalWrite(c, 1);
	      digitalWrite(d, 1);
	      digitalWrite(e, 1);
	      digitalWrite(f, 1);
	      digitalWrite(g, 1);
	      break;
	    case 12:
	      // C ->	0 1 1 1 0 0 1
	      digitalWrite(a, 1);
	      digitalWrite(b, 0);
	      digitalWrite(c, 0);
	      digitalWrite(d, 1);
	      digitalWrite(e, 1);
	      digitalWrite(f, 1);
	      digitalWrite(g, 0);
	      break;
	    case 14:
	      // E ->	1 1 1 1 0 0 1
	      digitalWrite(a, 1);
	      digitalWrite(b, 0);
	      digitalWrite(c, 0);
	      digitalWrite(d, 1);
	      digitalWrite(e, 1);
	      digitalWrite(f, 1);
	      digitalWrite(g, 1);
	      break;
	    case 13:
	      //  d ->	1 0 1 1 1 1 0
	      digitalWrite(a, 0);
	      digitalWrite(b, 1);
	      digitalWrite(c, 1);
	      digitalWrite(d, 1);
	      digitalWrite(e, 1);
	      digitalWrite(f, 0);
	      digitalWrite(g, 1);
	      break;
	    case 15:
	      // F ->	1 1 1 0 0 0 1
	      digitalWrite(a, 1);
	      digitalWrite(b, 0);
	      digitalWrite(c, 0);
	      digitalWrite(d, 0);
	      digitalWrite(e, 1);
	      digitalWrite(f, 1);
	      digitalWrite(g, 1);
	      break;
	    default:
	      // Turn off
	      digitalWrite(a, 0);
	      digitalWrite(b, 0);
	      digitalWrite(c, 0);
	      digitalWrite(d, 0);
	      digitalWrite(e, 0);
	      digitalWrite(f, 0);
	      digitalWrite(g, 0);
	      break;
	  }
	}