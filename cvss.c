#include<stdio.h>
#include<string.h>
#include<math.h>

// Function declarations (Base, Temporal, Environmental)

//function declaration for base
float AccessComplexity();
float Authentication();
float AccessVector();
float ConfidentialityImpact();
float IntegrityImpact();
float AvailabilityImpact();
void printbase();

//function declaration for temporal
float Exploitability();
float RemediationLevel();
float ReportConfidence();

//function declaration for environmental
float CollateralDamagePotential();
float TargetDistribution();
float ConfidentialityRequirement();
float IntegrityRequirement();
float AvailabilityRequirement();

// Structures to store Base, Temporal, and Environmental data
struct base {
    float Impact, Exploitability, BaseScore, CImp, IImp, AImp;
};

struct temporal {
    float TemporalScore, ReLe, ReCo;
};

struct environmental {
    float EnvironmentalScore, AdjustedTemporal, AdjustedImpact;
};

// Function prototypes for calculations
struct base calculate();
struct temporal calculate1(struct base temp);  // Pass base structure
struct environmental calculate2(struct base temp1, struct temporal temp2);  // Pass both base and temporal structures

// Function definitions for Base score
float AccessComplexity() {
    char ac1;
    float AC;
    printf("Enter score of AccessComplexity (h/m/l):\n");
    scanf(" %c", &ac1);
    switch(ac1) {
        case 'h': AC = 0.35; break;
        case 'm': AC = 0.61; break;
        case 'l': AC = 0.71; break;
        default: printf("Please enter a valid CVSS Score\n"); AC = 0.0; break;
    }
    return AC;
}

float Authentication() {
    char ac2;
    float Au;
    printf("Enter score of authentication (n/s/m):\n");
    scanf(" %c", &ac2);
    switch(ac2) {
        case 'n': Au = 0.704; break;
        case 's': Au = 0.56; break;
        case 'm': Au = 0.45; break;
        default: printf("Please enter a valid CVSS Score\n"); Au = 0.0; break;
    }
    return Au;
}

float AccessVector() {
    char ac3;
    float AV;
    printf("Enter score of AccessVector (l/a/n):\n");
    scanf(" %c", &ac3);
    switch(ac3) {
        case 'l': AV = 0.395; break;
        case 'a': AV = 0.646; break;
        case 'n': AV = 1; break;
        default: printf("Please enter a valid CVSS Metric Score\n"); AV = 0.0; break;
    }
    return AV;
}

float ConfidentialityImpact() {
    char ac4;
    float C;
    printf("Enter score of Confidentiality Impact (n/p/c):\n");
    scanf(" %c", &ac4);
    switch(ac4) {
        case 'n': C = 0.00; break;
        case 'p': C = 0.275; break;
        case 'c': C = 0.660; break;
        default: printf("Please enter a valid CVSS Score\n"); C = 0.0; break;
    }
    return C;
}

float IntegrityImpact() {
    char ac5;
    float I;
    printf("Enter the score of Integrity Impact (n/p/c):\n");
    scanf(" %c", &ac5);
    switch(ac5) {
        case 'n': I = 0.00; break;
        case 'p': I = 0.275; break;
        case 'c': I = 0.660; break;
        default: printf("Please enter a valid CVSS Score\n"); I = 0.0; break;
    }
    return I;
}

float AvailabilityImpact() {
    char ac6;
    float A;
    printf("Enter the score of availability Impact (n/p/c):\n");
    scanf(" %c", &ac6);
    switch(ac6) {
        case 'n': A = 0.00; break;
        case 'p': A = 0.275; break;
        case 'c': A = 0.660; break;
        default: printf("Please enter a valid CVSS Score\n"); A = 0.0; break;
    }
    return A;
}

// Base score calculation function
struct base calculate() {
    float AC, Au, AV, C, I, A, fi;
    struct base store;
    
    AC = AccessComplexity();
    Au = Authentication();
    AV = AccessVector();
    C = ConfidentialityImpact();
    I = IntegrityImpact();
    A = AvailabilityImpact();
    
    store.CImp = C;
    store.IImp = I;
    store.AImp = A;
    
    // Impact Calculation
    store.Impact = 10.41 * (1 - (1 - C) * (1 - I) * (1 - A));
    
    // Exploitability Calculation
    store.Exploitability = 20 * AC * Au * AV;
    
    // BaseScore Calculation
    fi = (store.Impact == 0) ? 0 : 1.176;
    store.BaseScore = (0.6 * store.Impact + 0.4 * store.Exploitability - 1.5) * fi;
    
    printf("Base Score: %f\n", store.BaseScore);
    return store;
}

// Temporal score calculation function
struct temporal calculate1(struct base temp) {
    float E, RL, RC;
    struct temporal store1;
    
    printf("Enter Exploitability score (u/p/f/h/n):\n");
    scanf(" %c", &E);
    
    printf("Enter Remediation Level (o/t/w/u/n):\n");
    scanf(" %c", &RL);
    
    printf("Enter Report Confidence (f/u/c/n):\n");
    scanf(" %c", &RC);
    
    store1.TemporalScore = temp.BaseScore * E * RL * RC;
    printf("Temporal Score: %f\n", store1.TemporalScore);
    return store1;
}

// Environmental score calculation function
struct environmental calculate2(struct base temp1, struct temporal temp2) {
    float CDP, TD, CR, IR, AR;
    struct environmental store2;
    
    // Environmental factors
    printf("Enter Collateral Damage Potential (n/w/l/m/h/d):\n");
    scanf(" %c", &CDP);
    
    printf("Enter Target Distribution (n/l/m/h/d):\n");
    scanf(" %c", &TD);
    
    printf("Enter Confidentiality Requirement (l/m/h/n):\n");
    scanf(" %c", &CR);
    
    printf("Enter Integrity Requirement (l/m/h/n):\n");
    scanf(" %c", &IR);
    
    printf("Enter Availability Requirement (l/m/h/n):\n");
    scanf(" %c", &AR);
    
    // Calculate adjusted impact and temporal score
    store2.AdjustedImpact = 10 < (10.41 * (1 - (1 - temp1.CImp * CR) * (1 - temp1.IImp * IR) * (1 - temp1.AImp * AR))) ? 10 : (10.41 * (1 - (1 - temp1.CImp * CR) * (1 - temp1.IImp * IR) * (1 - temp1.AImp * AR)));
    store2.AdjustedTemporal = (0.6 * store2.AdjustedImpact + 0.4 * temp1.Exploitability - 1.5) * 1.176 * temp1.Exploitability * temp2.ReLe * temp2.ReCo;
    store2.EnvironmentalScore = ((store2.AdjustedTemporal + (10 - store2.AdjustedTemporal)) * CDP * TD);
    
    printf("Environmental Score: %f\n", store2.EnvironmentalScore);
    return store2;
}

int main() {
    struct base temp = calculate();  // Get Base score
    struct temporal temp1 = calculate1(temp);  // Pass base to temporal calculation
    struct environmental temp2 = calculate2(temp, temp1);  // Pass both base and temporal to environmental calculation
    return 0;
}
