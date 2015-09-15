#ifndef DOMINANCE_STATUS_HPP
#define DOMINANCE_STATUS_HPP

enum class DominanceStatus {
  A_DOM_B,
  B_DOM_A,
  A_PART_DOM_B,
  B_PART_DOM_A,
  NO_DOM,
  MUTUAL_DOM
};

#endif  // DOMINANCE_STATUS_HPP
