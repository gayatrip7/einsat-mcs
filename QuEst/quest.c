#include <stdio.h>
#include <stdlib.h>

#define STATE_DIM 2     // Dimension of state vector
#define OBS_DIM 2       // Dimension of observation vector

// Kalman filter variables
float x_hat[STATE_DIM] = {0};           // Estimated state vector
float P[STATE_DIM][STATE_DIM] = {{1,0},{0,1}};   // Covariance matrix
float F[STATE_DIM][STATE_DIM] = {{1,1},{0,1}};   // State transition matrix
float Q[STATE_DIM][STATE_DIM] = {{1,0},{0,1}};   // Process noise covariance matrix
float R[OBS_DIM][OBS_DIM] = {{1,0},{0,1}};       // Measurement noise covariance matrix
float H[OBS_DIM][STATE_DIM] = {{1,0},{0,1}};     // Observation model matrix

// Kalman filter functions
void predict(void);
void update(float *z);

int main(void) {
    // Simulate measurements
    float z[OBS_DIM] = {10, 0}; // Position measurement
    
    // Run Kalman filter
    predict();
    update(z);
    
    // Print results
    printf("x_hat = [%f, %f]\n", x_hat[0], x_hat[1]);
    
    return 0;
}

void predict(void) {
    // Predict state estimate
    float x_hat_temp[STATE_DIM] = {0};
    for (int i=0; i<STATE_DIM; i++) {
        for (int j=0; j<STATE_DIM; j++) {
            x_hat_temp[i] += F[i][j] * x_hat[j];
        }
    }
    for (int i=0; i<STATE_DIM; i++) {
        x_hat[i] = x_hat_temp[i];
    }
    
    // Predict covariance matrix
    float P_temp[STATE_DIM][STATE_DIM] = {{0}};
    for (int i=0; i<STATE_DIM; i++) {
        for (int j=0; j<STATE_DIM; j++) {
            for (int k=0; k<STATE_DIM; k++) {
                P_temp[i][j] += F[i][k] * P[k][j];
            }
        }
    }
    for (int i=0; i<STATE_DIM; i++) {
        for (int j=0; j<STATE_DIM; j++) {
            P[i][j] = P_temp[i][j] + Q[i][j];
        }
    }
}

void update(float *z) {
    // Compute Kalman gain
    float K[STATE_DIM][OBS_DIM] = {{0}};
    float K_temp[STATE_DIM][OBS_DIM] = {{0}};
    float S[OBS_DIM][OBS_DIM] = {{0}};
    float S_temp[OBS_DIM][OBS_DIM] = {{0}};
    for (int i=0; i<STATE_DIM; i++) {
        for (int j=0; j<OBS_DIM; j++) {
            for (int k=0; k<STATE_DIM; k++) {
                K_temp[i][j] += P[i][k] * H[j][k];
            }
            S_temp[j][j] += H[j][i] * K_temp[i][j];
        }
    }
}
