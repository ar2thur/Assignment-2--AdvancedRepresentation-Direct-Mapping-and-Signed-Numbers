#include <stdint.h>
#include <stdio.h>
#include <string.h>


void oct_to_bin(const char *oct, char *out) {
    const char* lookup[] = {"000", "001", "010", "011", "100", "101", "110", "111"};
    
    out[0] = '\0';
    
    
    for (int i = 0; oct[i] != '\0'; i++) {
        int digit = oct[i] - '0';
        
        if (digit >= 0 && digit <= 7) {
            strcat(out, lookup[digit]);
        }
    }
}

void oct_to_hex(const char *oct, char *out) {
    char binary[100];
    oct_to_bin(oct, binary);
    
    out[0] = '\0';
    
    int bin_len = strlen(binary);
    int padding = (4 - (bin_len % 4)) % 4;
    char padded[100] = "";
    
    for (int i = 0; i < padding; i++) {
        strcat(padded, "0");
    }
    strcat(padded, binary);
    
    const char* hex_lookup[] = {"0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"};
    
    for (int i = 0; i < strlen(padded); i += 4) {
        int value = 0;
        for (int j = 0; j < 4; j++) {
            value = value * 2 + (padded[i + j] - '0');
        }
        strcat(out, hex_lookup[value]);
    }
    
    
    if (strlen(out) > 1) {
        char temp[100];
        strcpy(temp, out);
        int start = 0;
        while (temp[start] == '0' && temp[start + 1] != '\0') {
            start++;
        }
        strcpy(out, temp + start);
    }
}

void hex_to_bin(const char *hex, char *out) {
    const char* lookup[] = {"0000", "0001", "0010", "0011", 
                           "0100", "0101", "0110", "0111",
                           "1000", "1001", "1010", "1011", 
                           "1100", "1101", "1110", "1111"};
    
    out[0] = '\0';
    
    for (int i = 0; hex[i] != '\0'; i++) {
        char c = hex[i];
        int digit;
        
        if (c >= '0' && c <= '9') {
            digit = c - '0';
        } else if (c >= 'A' && c <= 'F') {
            digit = c - 'A' + 10;
        } else if (c >= 'a' && c <= 'f') {
            digit = c - 'a' + 10;
        } else {
            continue;
        }
        
        strcat(out, lookup[digit]);
    }
}

void to_sign_magnitude(int n, char *out) {
    for (int i = 0; i < 32; i++) {
        out[i] = '0';
    }
    out[32] = '\0';
    
    int magnitude = (n < 0) ? -n : n;
    
    
    for (int i = 31; i >= 0 && magnitude > 0; i--) {
        out[i] = (magnitude % 2) + '0';
        magnitude /= 2;
    }
    
    
    if (n < 0) {
        out[0] = '1';
    }
}
void to_ones_complement(int n, char *out) {

    for (int i = 0; i < 32; i++) {
        out[i] = '0';
    }
    out[32] = '\0';
    
    if (n >= 0) {
        
        int temp = n;
        for (int i = 31; i >= 0 && temp > 0; i--) {
            out[i] = (temp % 2) + '0';
            temp /= 2;
        }
    } else {
        
        int magnitude = -n;
        char positive[33];
        
        
        for (int i = 0; i < 32; i++) {
            positive[i] = '0';
        }
        positive[32] = '\0';
        
        for (int i = 31; i >= 0 && magnitude > 0; i--) {
            positive[i] = (magnitude % 2) + '0';
            magnitude /= 2;
        }
        
        
        for (int i = 0; i < 32; i++) {
            out[i] = (positive[i] == '0') ? '1' : '0';
        }
    }
}

void to_twos_complement(int n, char *out) {
    for (int i = 0; i < 32; i++) {
        out[i] = '0';
    }
    out[32] = '\0';
    
    if (n == 0) {
        return;
    }
    
    if (n > 0) {
        int temp = n;
        for (int i = 31; i >= 0 && temp > 0; i--) {
            out[i] = (temp % 2) + '0';
            temp /= 2;
        }
    } 
    else if (n == -2147483648) {
        //edge case
        strcpy(out, "10000000000000000000000000000000");
    }
    else {
        int magnitude = -n;
        
        //posituve
        for (int i = 31; i >= 0 && magnitude > 0; i--) {
            out[i] = (magnitude % 2) + '0';
            magnitude /= 2;
        }
        
        
        for (int i = 0; i < 32; i++) {
            out[i] = (out[i] == '0') ? '1' : '0';
        }
        
        
        int carry = 1;
        for (int i = 31; i >= 0 && carry; i--) {
            if (out[i] == '0') {
                out[i] = '1';
                carry = 0;
            } else {
                out[i] = '0';
            }
        }
    }
}

//its beautiful, im learning so much