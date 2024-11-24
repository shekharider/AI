% Facts (symptoms for different patients)
symptom(rahul, cough).
symptom(rahul, fever).
symptom(rahul, headache).

symptom(sita, cough).
symptom(sita, runny_nose).

symptom(akshay, headache).
symptom(akshay, fatigue).

% Rules for diseases
disease(Patient, flu) :- 
    symptom(Patient, cough),
    symptom(Patient, fever),
    symptom(Patient, headache).

disease(Patient, cold) :- 
    symptom(Patient, cough),
    symptom(Patient, runny_nose).

disease(Patient, migraine) :- 
    symptom(Patient, headache),
    symptom(Patient, fatigue).

% Example usage
% To find the disease for any patient:
% ?- disease(Patient, Disease).
% diagnose([fever, cough, cold, headache], Diseases).
%["fileName.pl"]
