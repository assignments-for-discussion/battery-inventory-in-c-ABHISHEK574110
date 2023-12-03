#include <stdio.h>
#include <assert.h>

struct CountsBySoH {
  int healthy;
  int exchange;
  int failed;
};

struct CountsBySoH countBatteriesByHealth(const int* presentCapacities, int nBatteries) {
 struct CountsBySoH counts = {0, 0, 0}; // initialize the counts to zero
 const int ratedCapacity = 120; // assume all batteries have the same rated capacity
 for (int i = 0; i < nBatteries; i++) { // loop through the array of present capacities
  int presentCapacity = presentCapacities[i]; // get the current battery's present capacity
  double soh = 100.0 * presentCapacity / ratedCapacity; // calculate the SoH percentage
  if (soh > 80) { // if SoH is more than 80%, the battery is healthy
   counts.healthy++; // increment the count of healthy batteries
  } else if (soh >= 62) { // if SoH is between 80% and 62%, the battery can be exchanged
   counts.exchange++; // increment the count of exchange batteries
  } else { // if SoH is below 62%, the battery has failed
   counts.failed++; // increment the count of failed batteries
  }
 }
 return counts; // return the struct with the counts
}


void testBucketingByHealth() {
  const int presentCapacities[] = {113, 116, 80, 95, 92, 70};
  const int numberOfBatteries = sizeof(presentCapacities) / sizeof(presentCapacities[0]);
  printf("Counting batteries by SoH...\n");
  struct CountsBySoH counts = countBatteriesByHealth(presentCapacities, numberOfBatteries);
  assert(counts.healthy == 2);
  assert(counts.exchange == 3);
  assert(counts.failed == 1);
  printf("Done counting :)\n");
}

int main() {
  testBucketingByHealth();
  return 0;
}
