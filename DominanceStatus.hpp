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

inline DominanceStatus invert(DominanceStatus ds) {
  switch (ds) {
    case DominanceStatus::A_DOM_B : return DominanceStatus::B_DOM_A;
    case DominanceStatus::B_DOM_A : return DominanceStatus::A_DOM_B;
    case DominanceStatus::A_PART_DOM_B : return DominanceStatus::B_PART_DOM_A;
    case DominanceStatus::B_PART_DOM_A : return DominanceStatus::A_PART_DOM_B;
    default : return ds;
  };
}

#endif  // DOMINANCE_STATUS_HPP
