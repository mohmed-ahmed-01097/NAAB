/*
 * SPIFFS_prog.c
 *
 *  Created on: Sep 13, 2024
 *      Author: MAAM
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SPIFFS_init.h"

#define WIFI_CREDENTIALS_PATH		"/spiffs/wifi_credentials.txt"
#define TAG 						"SPIFFS"

// Function to initialize SPIFFS
esp_err_t init_spiffs(void) {
    esp_vfs_spiffs_conf_t conf = {
        .base_path = "/spiffs",
        .partition_label = NULL,
        .max_files = 5, // Max number of open files
        .format_if_mount_failed = true
    };

    esp_err_t ret = esp_vfs_spiffs_register(&conf);

    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(TAG, "Failed to mount or format filesystem");
        } else if (ret == ESP_ERR_NOT_FOUND) {
            ESP_LOGE(TAG, "Failed to find SPIFFS partition");
        } else {
            ESP_LOGE(TAG, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
        }
        return ret;
    }

    size_t total = 0, used = 0;
    ret = esp_spiffs_info(NULL, &total, &used);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to get SPIFFS partition information (%s)", esp_err_to_name(ret));
    } else {
        ESP_LOGI(TAG, "SPIFFS total: %d, used: %d", total, used);
    }

    // Check consistency of reported partiton size info.
    if (used > total) {
        ESP_LOGW(TAG, "Number of used bytes cannot be larger than total. Performing SPIFFS_check().");
        ret = esp_spiffs_check(conf.partition_label);
        // Could be also used to mend broken files, to clean unreferenced pages, etc.
        // More info at https://github.com/pellepl/spiffs/wiki/FAQ#powerlosses-contd-when-should-i-run-spiffs_check
        if (ret != ESP_OK) {
            ESP_LOGE(TAG, "SPIFFS_check() failed (%s)", esp_err_to_name(ret));
            return ESP_FAIL;
        } else {
            ESP_LOGI(TAG, "SPIFFS_check() successful");
        }
    }

    return ESP_OK;
}

// Function to write WiFi SSID and password to SPIFFS
esp_err_t write_wifi_credentials(const char *ssid, const char *password) {
    // Initialize SPIFFS
    esp_err_t ret = init_spiffs();
    if (ret != ESP_OK) {
        return ret;
    }

    // First create a file.
    ESP_LOGI(TAG, "Opening file");
    // Open file for writing
    FILE* f = fopen(WIFI_CREDENTIALS_PATH, "w");
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open file for writing");
        return ESP_FAIL;
    }

    // Write SSID and password to file
    fprintf(f, "SSID: %s\nPASSWORD: %s\n", ssid, password);
    fclose(f);
    ESP_LOGI(TAG, "WiFi credentials written to %s", WIFI_CREDENTIALS_PATH);

    // Optionally, unmount SPIFFS if no longer needed
    esp_vfs_spiffs_unregister(NULL);
    ESP_LOGI(TAG, "SPIFFS unmounted");

    return ESP_OK;
}

// Function to read WiFi SSID and password from SPIFFS
esp_err_t read_wifi_credentials(char *ssid, size_t ssid_len, char *password, size_t password_len) {
    // Initialize SPIFFS
    esp_err_t ret = init_spiffs();
    if (ret != ESP_OK) {
        return ret;
    }

    // Open file for reading
    FILE* f = fopen(WIFI_CREDENTIALS_PATH, "r");
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open file for reading");
        return ESP_FAIL;
    }

    // Read SSID and password from file
    char line[128];
    while (fgets(line, sizeof(line), f) != NULL) {
        if (strncmp(line, "SSID: ", 6) == 0) {
            strncpy(ssid, line + 6, ssid_len - 1);
            ssid[strcspn(ssid, "\n")] = '\0'; // Remove newline character
        } else if (strncmp(line, "PASSWORD: ", 10) == 0) {
            strncpy(password, line + 10, password_len - 1);
            password[strcspn(password, "\n")] = '\0'; // Remove newline character
        }
    }
    fclose(f);
    ESP_LOGI(TAG, "WiFi credentials read from %s", WIFI_CREDENTIALS_PATH);

    // Optionally, unmount SPIFFS if no longer needed
    esp_vfs_spiffs_unregister(NULL);
    ESP_LOGI(TAG, "SPIFFS unmounted");

    return ESP_OK;
}

// Example usage
void spiffs_test(void) {
    const char *ssid = "Your_SSID";
    const char *password = "Your_PASSWORD";

    // Write credentials to file
    if (write_wifi_credentials(ssid, password) == ESP_OK) {
        ESP_LOGI(TAG, "WiFi credentials saved successfully.");
    } else {
        ESP_LOGE(TAG, "Failed to save WiFi credentials.");
    }

    // Prepare buffers to read credentials
    char read_ssid[64] = {0};
    char read_password[64] = {0};

    // Read credentials from file
    if (read_wifi_credentials(read_ssid, sizeof(read_ssid), read_password, sizeof(read_password)) == ESP_OK) {
        ESP_LOGI(TAG, "Read SSID: %s", read_ssid);
        ESP_LOGI(TAG, "Read Password: %s", read_password);
    } else {
        ESP_LOGE(TAG, "Failed to read WiFi credentials.");
    }
}


