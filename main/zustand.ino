int zustand_main = 0;
int zustand_sub = 0;


int zustand_begin()
{
  
}

void zustand_change(int new_zustand_main, int new_zustand_sub)
{
  zustand_main = new_zustand_main;
  zustand_sub = new_zustand_sub;
}

void zustand_print()
{
  Serial.print(zustand_main);
  Serial.print(";");
  Serial.print(zustand_sub);
  Serial.println("z");
}


/*                                                                               

1
2
4
4
5








*/

