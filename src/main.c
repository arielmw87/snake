#include <Arduino.h>
#include <util.h>

#define MAX_SNAKE_LEN 30

#define MATRIX_X 24
#define MATRIX_Y 8

#define bot_up PD0
#define bot_down PD1
#define bot_left PD2
#define bot_right PD3

#define led_data PD4
#define led_clk PD5
#define led_latch PB0

typedef struct point
{
  int x;
  int y;
} point;

void refresh_matrix(uint8_t *buff);

int main(void)
{

  uint8_t disp_buff[MATRIX_X];

  point apple;
  point snake_head;
  uint8_t snake_len;
  point snake_body[MAX_SNAKE_LEN];

  // creo la primer manzana
  apple.x = rand() % MATRIX_X;
  apple.y = rand() % MATRIX_Y;

  // ubico la vivora en el centro (aprox) de la matriz

  snake_head.x = MATRIX_Y / 2;
  snake_head.y = MATRIX_Y / 2;

  // inicializo cuerpo de la vivora
  snake_len = 0;
  for (uint8_t i = 0; i < MAX_SNAKE_LEN; i++)
  {
    snake_body[i].x = 0;
    snake_body[i].y = 0;
  }

  point direction;
  direction.x = 0;
  direction.y = 0;
  // cada loop del while es un frame, es es decir un avance de la vivora.
  while (1)
  {
    // defino sentido de movimiento en funcion del usuario
    if (bit_is_clear(PORTD, bot_up))
    {
      direction.x = 1;
      direction.y = 0;
    }
    if (bit_is_clear(PORTD, bot_down))
    {
      direction.x = -1;
      direction.y = 0;
    }
    if (bit_is_clear(PORTD, bot_left))
    {
      direction.x = 0;
      direction.y = -1;
    }
    if (bit_is_clear(PORTD, bot_right))
    {
      direction.x = 0;
      direction.y = 1;
    }

    // muevo la vivorita
    snake_head.x += direction.x;
    snake_head.y += direction.y;

    if ( (snake_head.x == apple.x) && (snake_head.y == apple.y))
    {
      snake_len++;
      // creo la siguiente manzana
      apple.x = rand() % MATRIX_X;
      apple.y = rand() % MATRIX_Y;
    }

    // actualizo posicion del cuerpo
    for (uint8_t i = snake_len; i > 0; i--)
    {
      snake_body[i].x = snake_body[i - 1].x;
      snake_body[i].y = snake_body[i - 1].y;
    }
    snake_body[0].x = snake_head.x;
    snake_body[0].y = snake_head.y;

    //--------------------------------------------------------------
    //--------------------------------------------------------------
    //-------- ACTUALIZO DISPLAY -----------------------------------
    //--------------------------------------------------------------
    //--------------------------------------------------------------
    // limpio buffer de salida

    memset(disp_buff, 0, sizeof(disp_buff));
    // for(uint8_t i = 0 ; i < MATRIX_X ; i++){
    //   disp_buff[i] = 0;
    // }

    // convierto coordenadas a matriz ( render(? )

    // prendo led de manzana
    disp_buff[apple.x] |= (1 << apple.y);
    // prendo cabeza de la vivora
    disp_buff[snake_head.x] |= (1 << snake_head.y);
    // prendo cuerpo de la vivora
    for (uint8_t i = 0; i < snake_len; i++)
    {
      disp_buff[snake_body[i].x] |= (1 << snake_body[i].y);
    }

    // refresco matriz de leds
    refresh_matrix(disp_buff);
  }
}

void refresh_matrix(uint8_t *buff)
{

  uint8_t tmp = 0;

  for (uint8_t i = 0; i < MATRIX_X; i++)
  {
    tmp = buff[i];
    for (uint8_t j = 0; j < 8; j++)
    {
      if ((tmp & 0x01) != 0)
      {
        set_bit(PORTD, led_data);
      }
      else
      {
        clear_bit(PORTD, led_data);
      }
      tmp >>= 1;
      set_bit(PORTD, led_clk);
      clear_bit(PORTD, led_clk);
    }

    set_bit(PORTD, led_latch);
    clear_bit(PORTD, led_latch);
  }

  // envio buffer a registros de desplazamiento.

  return;
}