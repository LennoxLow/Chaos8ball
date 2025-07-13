#include <Wire.h>
#include <U8g2lib.h>
#include "esp_sleep.h"
#include "driver/gpio.h"

// --- Pin Configuration ---
#define TAP_GPIO 3  // GPIO connected to tap/shock module
#define TAP_PIN_MASK (1ULL << TAP_GPIO)

// --- OLED Display Setup ---
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(
  U8G2_R0,        // Rotation
  U8X8_PIN_NONE,  // Reset pin
  4,              // Clock (SCL)
  5               // Data (SDA)
);

// --- Cursed 8 Ball Responses ---
// Full list of response examples in responses.txt
const char* answers[] = {
  "Chaos",
  "YES",
  "NO",
  "MAYBE"
};

// --- Text Wrapping and Centering ---
void drawWrappedCenteredText(const char* text, int maxWidth, int lineHeight, int screenHeight) {
  char buffer[256];
  strncpy(buffer, text, sizeof(buffer));
  buffer[sizeof(buffer) - 1] = '\0';

  char* word = strtok(buffer, " ");
  String line = "";
  std::vector<String> lines;

  while (word != nullptr) {
    String testLine = line + word + " ";
    int width = u8g2.getUTF8Width(testLine.c_str());

    if (width > maxWidth && !line.isEmpty()) {
      lines.push_back(line);
      line = String(word) + " ";
    } else {
      line = testLine;
    }

    word = strtok(nullptr, " ");
  }

  if (!line.isEmpty()) {
    lines.push_back(line);
  }

  int totalHeight = lines.size() * lineHeight;
  int y = (screenHeight - totalHeight) / 2 + lineHeight;

  for (const auto& ln : lines) {
    int textWidth = u8g2.getUTF8Width(ln.c_str());
    int x = (128 - textWidth) / 2;
    u8g2.drawUTF8(x, y, ln.c_str());
    y += lineHeight;
  }
}

// --- Display Response ---
void show8BallResponse() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_helvB08_tr);

  int index = random(0, sizeof(answers) / sizeof(answers[0]));
  const char* message = answers[index];

  drawWrappedCenteredText(message, 128, 12, 64);
  u8g2.sendBuffer();

  Serial.println("Displayed: " + String(message));
}

// --- Deep Sleep ---
void goToSleep() {
  Serial.println("Going to sleep...");

  u8g2.clearDisplay();
  u8g2.sleepOn();
  delay(100);

  gpio_hold_en((gpio_num_t)TAP_GPIO);
  gpio_pullup_en((gpio_num_t)TAP_GPIO);

  esp_deep_sleep_enable_gpio_wakeup(TAP_PIN_MASK, ESP_GPIO_WAKEUP_GPIO_LOW);
  esp_deep_sleep_start();
}

// --- Setup ---
void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("Booting...");

  u8g2.begin();

  pinMode(TAP_GPIO, INPUT_PULLUP);
  gpio_pullup_en((gpio_num_t)TAP_GPIO);

  if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_GPIO) {
    Serial.println("Woken by tap!");
  } else {
    Serial.println("Normal boot.");
  }

  show8BallResponse();
  delay(10000);  // Display duration

  goToSleep();
}

// --- Loop (Unused) ---
void loop() {
  // Not used — device sleeps after displaying message
}
