#include <stdio.h>
#include <stdlib.h>

#define MEASUREMENT_NOISE_VAR  0.1 // measurement noise variance
#define PROCESS_NOISE_VAR      0.01 // process noise variance

// Kalman filter struct
typedef struct {
    float x_hat;        // estimated state
    float p;            // error covariance
    float k;            // Kalman gain
    float q;            // process noise variance
    float r;            // measurement noise variance
} KalmanFilter;

// predict the next state
void kalman_filter_predict(KalmanFilter* filter) {
    // project the state ahead
    filter->x_hat = filter->x_hat;
    filter->p = filter->p + filter->q;
}

// update the estimated state based on the measurement
void kalman_filter_update(KalmanFilter* filter, float measurement) {
    // calculate the Kalman gain
    filter->k = filter->p / (filter->p + filter->r);
    
    // update the state estimate
    filter->x_hat = filter->x_hat + filter->k * (measurement - filter->x_hat);
    
    // update the error covariance
    filter->p = (1 - filter->k) * filter->p;
}

int main() {
    KalmanFilter filter;
    float measurement_data[] = {1.2, 1.4, 1.5, 1.7, 1.8}; // example measurement data
    int measurement_count = sizeof(measurement_data) / sizeof(float);
    float initial_state = 1.0; // initial state estimate
    float initial_covariance = 1.0; // initial covariance estimate
    
    // initialize the Kalman filter
    filter->x_hat = initial_state;
    filter->p = initial_covariance;
    filter->q = PROCESS_NOISE_VAR;
    filter->r = MEASUREMENT_NOISE_VAR;

    // perform Kalman filtering for each measurement
    for (int i = 0; i < measurement_count; i++) {
        // predict the next state
        kalman_filter_predict(&filter);
        
        // update the estimated state based on the measurement
        kalman_filter_update(&filter, measurement_data[i]);
        
        // print the estimated state
        printf("Estimated state after measurement %d: %f\n", i+1, filter.x_hat);
    }
    
    return 0;
}

