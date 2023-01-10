char corr_num_row[6] = {0,3,5,1,2,4}; //номера лучей в конструкции звезды для движении эффекта по часовой стрелке

void clear_img (void){
  for (int i = 0; i < MAX_LEDS; i++){
    strip.setPixelColor(i,0);
  }
}

void dimmer_off(){
  for (int i = 0; i < 10; i++){
    strip.setBrightness(255-i*25); 
    strip.show();
    delay(30);
  }
  clear_img();
  strip.setBrightness(255); 
}

void effect001(void){  //вращающиеся лучи
int i,j,num_kadr,cnt_kadr;

  for (num_kadr = 0; num_kadr < NUM_ROW; num_kadr++){ // цикл на изменения кадров.
    for (i = 0; i < NUM_STARS; i++) {  //цикл на кол-во звезд
      for (j = 0; j < LEN_ROW; j++) {  //цикл на кол-во светодиодов в луче.

        cnt_kadr = corr_num_row[(((i+num_kadr-1) % NUM_ROW) >= 0) ? (i+num_kadr-1) % NUM_ROW : LEN_ROW] * LEN_ROW;

        if (cnt_kadr > 4) {cnt_kadr++;} // //коррекция на центральную точку
        strip.setPixelColor(i * LEN_STAR + j + cnt_kadr, strip.gamma32(strip.ColorHSV(0,255,0)));

        cnt_kadr = corr_num_row[(i + num_kadr) % NUM_ROW] * LEN_ROW;
        if (cnt_kadr >4) {cnt_kadr++;} //коррекция на центральную точку
        strip.setPixelColor(i * LEN_STAR + j + cnt_kadr, strip.gamma32(strip.ColorHSV(0,255,255)));
      }
    }
    strip.show(); // Update strip with new contents
    delay(200);
  }
}
void effect002(void){  //бегущий огонь среди звезд
int j,num_kadr,cnt_kadr;

  for (num_kadr = 0; num_kadr < NUM_STARS; num_kadr++){ // цикл на изменения кадров. по количеству звезд
      for (j = 0; j < LEN_STAR; j++) {  //цикл на кол-во светодиодов в звезде

        cnt_kadr = (num_kadr-1) * LEN_STAR;
        if (cnt_kadr < 0) {cnt_kadr = (NUM_STARS-1)*LEN_STAR;}
        strip.setPixelColor(j + cnt_kadr, strip.gamma32(strip.ColorHSV(54000,255,25)));
        cnt_kadr = num_kadr * LEN_STAR;
        strip.setPixelColor(j + cnt_kadr, strip.gamma32(strip.ColorHSV(54000,255,255)));
      }
      strip.show(); // Update strip with new contents
      delay(200);
  }
}
void test_spinner_spiral_dot(){  //заполнение звезды точкой движущейся по спирали от внешнего края во внутрь
int i,j,m,temp,colr;
    for (i = 0; i < NUM_STARS; i++) {// цикл перебора звезд
      colr = 65535 - 6000*i;
      j = corr_num_row[cnt_j];  //номер луча
          m = cnt_k;
            if ((j%2)==0) {   //расчет светодиода из-за разного направления лучей(ленты) относительно центра. чётные лучи направлены к центру, а нечетные от центра
                  temp = m + i*LEN_STAR + j*LEN_ROW;
              if (j>0) {temp++;}              //коррекция на центральную точку
              } else{
                  temp = 4 - m + i*LEN_STAR + j*LEN_ROW;
                  if (j>0) {temp++;}               //коррекция на центральную точку
                  }
                  if ((temp>=0)&&(temp<MAX_LEDS)){  //проверка выхода за границы ленты
                  strip.setPixelColor(temp, strip.gamma32(strip.ColorHSV(colr,255,255)));
                  }
                  temp = 0;
    }
    strip.show(); // Update strip with new contents
    delay(120);

    cnt_j++;

    if (cnt_j>5) {
        cnt_j=0;
        cnt_k++;
        if (cnt_k>4) {
            cnt_k=0;
          delay(500);//конец эффекта. Пауза перед выключением
            for (i = 0; i < MAX_LEDS; i++){
              strip.setPixelColor(i, 0);
            }
          }
    }
     num_kadr++;
 if (num_kadr>LEN_ROW) {num_kadr = 0;}
}
void effect003(){   //попиксельное заполнение звёзд слева направо
int i=0,j=0,m=0,temp,colr;
int temp_row;

      i = cnt_i;
      colr =  6200*i;
      switch (stage){  // этапы выполнения эффектов
        case 0:  //нулевой - заполнение левых лучей от края к центру
          for (temp_row = 1; temp_row < 3; temp_row++) { // цикл перебора лучей
          j = corr_num_row[temp_row];
              for (m = 0; m < num_kadr; m++) {  //цикл для зажигания луча
              //m = 0;
                if ((j%2)==0) {   //расчет светодиода из-за разного направления лучей(ленты) относительно центра. чётные лучи направлены к центру, а нечетные от центра
                      temp = m + i*LEN_STAR + j*LEN_ROW;
                  if (j>0) {temp++;}              //коррекция на центральную точку
                  } else{
                      temp = 4 - m + i*LEN_STAR + j*LEN_ROW;
                      if (j>0) {temp++;}               //коррекция на центральную точку
                      }
                      if ((temp>=0)&&(temp<MAX_LEDS)){  //проверка выхода за границы ленты
                      strip.setPixelColor(temp, strip.gamma32(strip.ColorHSV(colr,255,250)));
                      }
                      temp = 0;
              } //цикл для зажигания луча
            } // цикл перебора лучей
          break;

         case 1:  //первый этап - включение вертикальных лучей
            for (j = 0; j < 2; j++) { // цикл перебора лучей
//              j = corr_num_row[temp_row];
                for (m = 0; m < 5; m++) {  //цикл для зажигания луча
                //m = 0;
                  if ((j%2)==0) {   //расчет светодиода из-за разного направления лучей(ленты) относительно центра. чётные лучи направлены к центру, а нечетные от центра
                        temp = m + i*LEN_STAR + j*LEN_ROW;
                    if (j>0) {temp++;}              //коррекция на центральную точку
                    } else{
                        temp = 4 - m + i*LEN_STAR + j*LEN_ROW;
                        if (j>0) {temp++;}               //коррекция на центральную точку
                        }
                        if ((temp>=0)&&(temp<MAX_LEDS)){  //проверка выхода за границы ленты
                          strip.setPixelColor(temp, strip.gamma32(strip.ColorHSV(colr,255,255)));
                        }
                        temp = 0;
                } //цикл для зажигания луча
            } // цикл перебора лучей
            num_kadr += 4;
            break;

          case 2:  // второй этап - заполнение правых лучей от центра к краю
          for (temp_row = 4; temp_row < 6; temp_row++) { // цикл перебора лучей
          j = corr_num_row[temp_row];
              for (m = 0; m < num_kadr%6; m++) {  //цикл для зажигания луча
              //m = 0;
                if ((j%2)!=0) {   //расчет светодиода из-за разного направления лучей(ленты) относительно центра. чётные лучи направлены к центру, а нечетные от центра
                      temp = m + i*LEN_STAR + j*LEN_ROW;
                  if (j>0) {temp++;}              //коррекция на центральную точку
                  } else{
                      temp = 4 - m + i*LEN_STAR + j*LEN_ROW;
                      if (j>0) {temp++;}               //коррекция на центральную точку
                      }
                      if ((temp>=0)&&(temp<MAX_LEDS)){  //проверка выхода за границы ленты
                      strip.setPixelColor(temp, strip.gamma32(strip.ColorHSV(colr,255,255)));
                      }
                      temp = 0;
              } //цикл для зажигания луча
            } // цикл перебора лучей

            break;

        default:
          break;
      }
    strip.show(); // Update strip with new contents
    delay(50);
    num_kadr++;
     if (num_kadr>LEN_ROW) {
         num_kadr = 0;
         stage += 1; //
         if (stage>2) {
             stage = 0;
             cnt_i += 1;
             if (cnt_i>NUM_STARS) {
                 cnt_i = 0;
                 clear_img();
               }
           }
       }
}  //void effect003(){   //заполнение звезды слева направо
void effect004(){  //(вращающиеся 2 луча по часовой стрелке)
int i,j,cnt_kadr;
    for (i = 0; i < NUM_STARS; i++) {  //цикл на кол-во звезд
      for (j = 0; j < LEN_ROW; j++) {  //цикл на кол-во светодиодов в луче.

        cnt_kadr = corr_num_row[((num_kadr-1)>=0) ? num_kadr-1 : LEN_ROW] * LEN_ROW;
        if (cnt_kadr > 4) {cnt_kadr++;} // //коррекция на центральную точку
        strip.setPixelColor(i * LEN_STAR + j + cnt_kadr, strip.gamma32(strip.ColorHSV(180*180,255,3)));

        cnt_kadr = corr_num_row[(((num_kadr+3)%NUM_ROW-1)>=0) ? (num_kadr+3)%NUM_ROW-1 : LEN_ROW] * LEN_ROW;
        if (cnt_kadr > 4) {cnt_kadr++;} // //коррекция на центральную точку
        strip.setPixelColor(i * LEN_STAR + j + cnt_kadr, strip.gamma32(strip.ColorHSV(180*180,255,3)));

        cnt_kadr = corr_num_row[num_kadr] * 5;
        if (cnt_kadr >4) {cnt_kadr++;} //коррекция на центральную точку
        strip.setPixelColor(i * LEN_STAR + j + cnt_kadr, strip.gamma32(strip.ColorHSV(180*180,255,255)));

        cnt_kadr = corr_num_row[(num_kadr+3)%6] * 5;
        if (cnt_kadr >4) {cnt_kadr++;} //коррекция на центральную точку
        strip.setPixelColor(i * LEN_STAR + j + cnt_kadr, strip.gamma32(strip.ColorHSV(180*180,255,255)));
      }
    }
    strip.show(); // Update strip with new contents
    delay(150);
    num_kadr++;
    if (num_kadr>LEN_ROW) {num_kadr = 0;}
}
void effect005(void){  //стробоскоп зеленый зеленый
#define PAUSE 25
#define CNT 8
#define COLOR1 0
#define COLOR2 120
#define VAL1 255
#define VAL2 45
#define VAL3 25


  for (char cnt = 0; cnt < CNT; cnt++){ //помигаем красным
    for (int i = 0; i < NUM_STARS;) {  //цикл на кол-во звезд
      for (int j = 0; j < LEN_STAR; j++) {  //цикл на кол-во светодиодов в звезде. Длина звезды
        strip.setPixelColor(i * LEN_STAR + j , strip.gamma32(strip.ColorHSV(COLOR1*180,255,VAL1)));
        }
      i++;
      i++;
    }
    strip.show(); // Update strip with new contents
    delay(PAUSE);
    for (int i = 0; i < NUM_STARS;) {  //цикл на кол-во звезд
      for (int j = 0; j < LEN_STAR; j++) {  //цикл на кол-во светодиодов в звезде. Длина звезды
        strip.setPixelColor(i * LEN_STAR + j , strip.gamma32(strip.ColorHSV(COLOR1*180,255,VAL2)));
       }
      i++;
      i++;
    }
    strip.show(); // Update strip with new contents
    delay(PAUSE);
  }
  //поставим красный на минимум яркости
  for (int i = 0; i < NUM_STARS;) {  //цикл на кол-во звезд
    for (int j = 0; j < LEN_STAR; j++) {  //цикл на кол-во светодиодов в звезде. Длина звезды
      strip.setPixelColor(i * LEN_STAR + j , strip.gamma32(strip.ColorHSV(COLOR1*180,255,VAL3)));
      }
    i++;
    i++;
    }

  for (char cnt = 0; cnt < CNT; cnt++){ //помигаем зеленым
    for (int i = 1; i < NUM_STARS;) {  //цикл на кол-во звезд
      for (int j = 0; j < LEN_STAR; j++) {  //цикл на кол-во светодиодов в звезде. Длина звезды
        strip.setPixelColor(i * LEN_STAR + j , strip.gamma32(strip.ColorHSV(COLOR2*180,255,VAL1)));
        }
      i++;
      i++;
    }
    strip.show(); // Update strip with new contents
    delay(PAUSE);
    for (int i = 1; i < NUM_STARS;) {  //цикл на кол-во звезд
      for (int j = 0; j < LEN_STAR; j++) {  //цикл на кол-во светодиодов в звезде. Длина звезды
        strip.setPixelColor(i * LEN_STAR + j , strip.gamma32(strip.ColorHSV(COLOR2*180,255,VAL2)));
        }
      i++;
      i++;
    }
    strip.show(); // Update strip with new contents
    delay(PAUSE);
  }
  //поставим зеленый на минимум
  for (int i = 1; i < NUM_STARS;) {  //цикл на кол-во звезд
      for (int j = 0; j < LEN_STAR; j++) {  //цикл на кол-во светодиодов в звезде. Длина звезды
        strip.setPixelColor(i * LEN_STAR + j , strip.gamma32(strip.ColorHSV(COLOR2*180,255,VAL3)));
        }
      i++;
      i++;
    }
}
void effect006(void){  //заполняющий огонь по всем лучам от краев к центру, затем погасание от краев к центру
int i,j,m,num_kadr,temp,color;
  clear_img();
  //заполняющий огонь от краёв к центру
  for (num_kadr = 0; num_kadr < LEN_ROW+1; num_kadr++){ // цикл на изменения кадров. по количеству светодиодов в луче
    for (i = 0; i < NUM_STARS; i++) {// цикл перебора звезд
      color = 36*i;
      for (j = 0; j <NUM_ROW; j++) { // цикл перебора лучей
          for (m = 0; m < num_kadr; m++) {  //цикл для зажигания луча
            if ((j%2)==0) {   //расчет светодиода из-за разного направления лучей(ленты) относительно центра. чётные лучи направлены к центру, а нечетные от центра
                  temp = m + i*LEN_STAR + j*LEN_ROW;
              if (j>0) {temp++;}              //коррекция на центральную точку
              } else {
                  temp = 4 - m + i*LEN_STAR + j*LEN_ROW;
                  if (j>0) {temp++;}              //коррекция на центральную точку
              }
              if ((temp>=0)&&(temp<MAX_LEDS)){  //проверка выхода за границы ленты
                  strip.setPixelColor(temp , strip.gamma32(strip.ColorHSV(color*180,255,255)));
              }
              temp = 0;
            }
        }
    }
    strip.show(); // Update strip with new contents
    delay(120);
  }
  // включение центральной точки
  for (i = 0; i < NUM_STARS; i++){
      strip.setPixelColor(i * LEN_STAR + 5 , strip.gamma32(strip.ColorHSV(6500*i,255,255)));
  }
  strip.show(); // Update strip with new contents
  delay(120);

  for (num_kadr = 0; num_kadr < LEN_ROW+1; num_kadr++){ // цикл на изменения кадров. по количеству светодиодов в луче
    for (i = 0; i < NUM_STARS; i++) {// цикл перебора звезд
      for (j = 0; j <NUM_ROW; j++) { // цикл перебора лучей
          for (m = 0; m < num_kadr; m++) {  //цикл для зажигания луча
            if ((j%2)==0) {   //расчет светодиода из-за разного направления лучей(ленты) относительно центра. чётные лучи направлены к центру, а нечетные от центра
                  temp = m + i*LEN_STAR + j*LEN_ROW;
                  if (j>0) {temp++;}
              } else{
                  temp = 4 - m + i*LEN_STAR + j*LEN_ROW;
                  if (j>0) {temp++;}
                  }
                  if ((temp>=0)&&(temp<MAX_LEDS)){
                  strip.setPixelColor(temp , strip.gamma32(strip.ColorHSV(180*180,255,0)));
                  }
                  temp = 0;
                }
              }
            }
        strip.show(); // Update strip with new contents
        delay(120);
  }
  // выключение центральной точки
  for (i = 0; i < NUM_STARS; i++){
      strip.setPixelColor(i * LEN_STAR + 5 , strip.gamma32(strip.ColorHSV(180*180,255,0)));
  }
  strip.show(); // Update strip with new contents
  delay(120);
}
void effect007(void){  //бегущий огонь среди звезд
int j,num_kadr,cnt_kadr;

  for (num_kadr = 0; num_kadr < NUM_STARS; num_kadr++){ // цикл на изменения кадров. по количеству звезд
      for (j = 0; j < LEN_STAR; j++) {  //цикл на кол-во светодиодов в звезде

        cnt_kadr = (num_kadr-1) * LEN_STAR;
        if (cnt_kadr < 0) {cnt_kadr = (NUM_STARS-1)*LEN_STAR;}
        strip.setPixelColor(j + cnt_kadr , strip.gamma32(strip.ColorHSV(220*180,255,25)));

        cnt_kadr = num_kadr * LEN_STAR;
        strip.setPixelColor(j + cnt_kadr , strip.gamma32(strip.ColorHSV(180*180,255,255)));
      }
      strip.show(); // Update strip with new contents
      delay(150);
  }
}
void effect008(void){  //бегущий огонь среди звезд со шлейфом
int j,m,num_kadr,cnt_kadr;
int lenShlf = 6;

  clear_img();

  for (num_kadr = 0; num_kadr < NUM_STARS + lenShlf - 1; num_kadr++){ // цикл на изменения кадров. по количеству звезд
    for (j = 0 ; j < lenShlf; j++)
    {
      if (((num_kadr-j)>=0)&&((num_kadr-j)<NUM_STARS)) {
        for (m = 0; m < LEN_STAR; m++) {  //цикл для зажигания одной цвезды одним цветом
          cnt_kadr = num_kadr * LEN_STAR;
          int temp = m + cnt_kadr - j*LEN_STAR;
          if ((temp>=0)&&(temp<MAX_LEDS)) {
            strip.setPixelColor(temp , strip.gamma32(strip.ColorHSV(180*180,255,(250-(j+1)*49)<0 ? 25 :(250-(j+1)*49))));
          }
        }
      }
    }

        for (m = 0; m < LEN_STAR; m++) {  //цикл для зажигания одной цвезды одним цветом
          cnt_kadr = num_kadr * LEN_STAR;
          int temp = m + cnt_kadr - lenShlf*LEN_STAR;
          if ((temp>=0)&&(temp<MAX_LEDS)) {
            strip.setPixelColor(temp , strip.gamma32(strip.ColorHSV(180*180,255,25)));
          }
        }
      strip.show(); // Update strip with new contents
      delay(110);
  }
}
