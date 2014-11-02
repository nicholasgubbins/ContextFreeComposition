//
//  All_Chords.h
//  Algorithmic Composer
//
//  Created by Nicholas Gubbins on 02/08/2014.
//  Copyright (c) 2014 Nicholas Gubbins. All rights reserved.
//

#ifndef Algorithmic_Composer_All_Chords_h
#define Algorithmic_Composer_All_Chords_h

//--------------------------------------------------------------------------------
//most chords defined in terms of western classical tradition
//--------------------------------------------------------------------------------
vector<int> C_MAJOR {0, 4, 7};
vector<int> C_SUS_4 {0, 5, 7};
vector<int> C_SUS_2 {0, 2, 7};
vector<int> C_MINOR {0, 3, 7};
vector<int> C_MINOR_SEVENTH {0, 3, 7, 10};
vector<int> C_DOM_SEVENTH {0, 4, 7, 10};
vector<int> C_MAJOR_SEVENTH {0, 4, 7, 11};
vector<int> C_DIM {0, 3, 6};
vector<int> C_DIM_SEVENTH {0, 3, 6, 9};
vector<int> C_HALF_DIM_SEVENTH {0, 3, 6, 10};
vector<int> C_AUG {0, 4, 8};

vector<int> C_SHARP_MAJOR {1, 5, 8};
vector<int> C_SHARP_MINOR {1, 4, 8};
vector<int> C_SHARP_SUS_4 {1, 6, 8};
vector<int> C_SHARP_SUS_2 {1, 3, 8};
vector<int> C_SHARP_MINOR_SEVENTH {1, 4, 8, 11};
vector<int> C_SHARP_DOM_SEVENTH {1, 5, 8, 11};
vector<int> C_SHARP_MAJOR_SEVENTH {0, 1, 5, 8};
vector<int> C_SHARP_DIM {1, 4, 7};
vector<int> C_SHARP_DIM_SEVENTH {1, 4, 7, 10};
vector<int> C_SHARP_HALF_DIM_SEVENTH {1, 4, 7, 11};
vector<int> C_SHARP_AUG {1, 5, 9};

vector<int> D_MAJOR {2, 6, 9};
vector<int> D_MINOR {2, 5, 9};
vector<int> D_SUS_4 {2, 7, 9};
vector<int> D_SUS_2 {2, 4, 9};
vector<int> D_MINOR_SEVENTH {0, 2, 5, 9};
vector<int> D_DOM_SEVENTH {0, 2, 6, 9};
vector<int> D_MAJOR_SEVENTH {1, 2, 6, 9};
vector<int> D_DIM {2, 5, 8};
vector<int> D_DIM_SEVENTH {2, 5, 8, 11};
vector<int> D_HALF_DIM_SEVENTH {0, 2, 5, 8};
vector<int> D_AUG {2, 6, 10};

vector<int> D_SHARP_MAJOR {3, 7, 10};
vector<int> D_SHARP_MINOR {3, 6, 10};
vector<int> D_SHARP_SUS_4 {3, 8, 10};
vector<int> D_SHARP_SUS_2 {3, 5, 10};
vector<int> D_SHARP_MINOR_SEVENTH {1, 3, 6, 10};
vector<int> D_SHARP_DOM_SEVENTH {1, 3, 7, 10};
vector<int> D_SHARP_MAJOR_SEVENTH {2, 3, 7, 10};
vector<int> D_SHARP_DIM {3, 6, 9};
vector<int> D_SHARP_HALF_DIM_SEVENTH {1, 3, 6, 9};
vector<int> D_SHARP_AUG {3, 7, 11};

vector<int> E_MAJOR {4, 8, 11};
vector<int> E_MINOR {4, 7, 11};
vector<int> E_SUS_4 {4, 9, 11};
vector<int> E_SUS_2 {4, 6, 11};
vector<int> E_MINOR_SEVENTH {2, 4, 7, 11};
vector<int> E_DOM_SEVENTH {2, 4, 8, 11};
vector<int> E_MAJOR_SEVENTH {3, 4, 8, 11};
vector<int> E_DIM {4, 7, 10};
vector<int> E_HALF_DIM_SEVENTH {2, 4, 7, 10};

vector<int> F_MAJOR {0, 5, 9};
vector<int> F_MINOR {0, 5, 8};
vector<int> F_SUS_4 {0, 5, 10};
vector<int> F_SUS_2 {0, 5, 7};
vector<int> F_MINOR_SEVENTH {0, 3, 5, 8};
vector<int> F_DOM_SEVENTH {0, 3, 5, 9};
vector<int> F_MAJOR_SEVENTH {0, 4, 5, 9};
vector<int> F_DIM {5, 8, 11};
vector<int> F_HALF_DIM_SEVENTH {3, 5, 8, 11};

vector<int> F_SHARP_MAJOR {1, 6, 10};
vector<int> F_SHARP_MINOR {1, 6, 9};
vector<int> F_SHARP_SUS_4 {1, 6, 11};
vector<int> F_SHARP_SUS_2 {1, 6, 8};
vector<int> F_SHARP_MINOR_SEVENTH {1, 4, 6, 9};
vector<int> F_SHARP_DOM_SEVENTH {1, 4, 6, 10};
vector<int> F_SHARP_MAJOR_SEVENTH {1, 5, 6, 10};
vector<int> F_SHARP_DIM {0, 6, 9};
vector<int> F_SHARP_HALF_DIM_SEVENTH {0, 4, 6, 9};

vector<int> G_MAJOR {2, 7, 11};
vector<int> G_MINOR {2, 7, 10};
vector<int> G_SUS_4 {0, 2, 7};
vector<int> G_SUS_2 {2, 7, 9};
vector<int> G_MINOR_SEVENTH {2, 5, 7, 10};
vector<int> G_DOM_SEVENTH {2, 5, 7, 11};
vector<int> G_MAJOR_SEVENTH {2, 6, 7, 11};
vector<int> G_DIM {1, 7, 10};
vector<int> G_HALF_DIM_SEVENTH {1, 5, 7, 10};

vector<int> G_SHARP_MAJOR {0, 3, 8};
vector<int> G_SHARP_MINOR {3, 8, 11};
vector<int> G_SHARP_SUS_4 {1, 3, 8};
vector<int> G_SHARP_SUS_2 {3, 8, 10};
vector<int> G_SHARP_MINOR_SEVENTH {3, 6, 8, 11};
vector<int> G_SHARP_DOM_SEVENTH {0, 3, 6, 8};
vector<int> G_SHARP_MAJOR_SEVENTH {0, 3, 7, 8};
vector<int> G_SHARP_DIM {2, 8, 11};
vector<int> G_SHARP_HALF_DIM_SEVENTH {2, 6, 8, 11};

vector<int> A_MAJOR {1, 4, 9};
vector<int> A_MINOR {0, 4, 9};
vector<int> A_SUS_4 {2, 4, 9};
vector<int> A_SUS_2 {4, 9, 11};
vector<int> A_MINOR_SEVENTH {0, 4, 7, 9};
vector<int> A_DOM_SEVENTH {1, 4, 7, 9};
vector<int> A_MAJOR_SEVENTH {1, 4, 8, 9};
vector<int> A_DIM {0, 3, 9};
vector<int> A_HALF_DIM_SEVENTH {0, 3, 7, 9};

vector<int> A_SHARP_MAJOR {2, 5, 10};
vector<int> A_SHARP_MINOR {1, 5, 10};
vector<int> A_SHARP_SUS_4 {3, 5, 10};
vector<int> A_SHARP_SUS_2 {0, 5, 10};
vector<int> A_SHARP_MINOR_SEVENTH {1, 5, 8, 10};
vector<int> A_SHARP_DOM_SEVENTH {2, 5, 8, 10};
vector<int> A_SHARP_MAJOR_SEVENTH {2, 5, 9, 10};
vector<int> A_SHARP_DIM {1, 4, 10};
vector<int> A_SHARP_HALF_DIM_SEVENTH {1, 4, 8, 10};

vector<int> B_MAJOR {3, 6, 11};
vector<int> B_MINOR {2, 6, 11};
vector<int> B_SUS_4 {4, 6, 11};
vector<int> B_SUS_2 {1, 6, 11};
vector<int> B_MINOR_SEVENTH {2, 6, 9, 11};
vector<int> B_DOM_SEVENTH {3, 6, 9, 11};
vector<int> B_MAJOR_SEVENTH {3, 6, 10, 11};
vector<int> B_DIM {2, 5, 11};
vector<int> B_HALF_DIM_SEVENTH {2, 5, 9, 11};

vector<vector<int>> MAJOR_TRIADS {C_MAJOR, C_SHARP_MAJOR, D_MAJOR, D_SHARP_MAJOR, E_MAJOR, F_MAJOR, F_SHARP_MAJOR, G_MAJOR, G_SHARP_MAJOR, A_MAJOR, A_SHARP_MAJOR, D_MAJOR};
vector<vector<int>> MINOR_TRIADS {C_MINOR, C_SHARP_MINOR, D_MINOR, D_SHARP_MINOR, E_MINOR, F_MINOR, F_SHARP_MINOR, G_MINOR, G_SHARP_MINOR, A_MINOR, A_SHARP_MINOR, B_MINOR};
vector<vector<int>> DIM_TRIADS {C_DIM, C_SHARP_DIM, D_DIM, D_SHARP_DIM, E_DIM, F_DIM, F_SHARP_DIM, G_DIM, G_SHARP_DIM, A_DIM, A_SHARP_DIM, B_DIM};
vector<vector<int>> SUS4_TRIADS {C_SUS_4, C_SHARP_SUS_4, D_SUS_4, D_SHARP_SUS_4, E_SUS_4, F_SUS_4, F_SHARP_SUS_4, G_SUS_4, G_SHARP_SUS_4, A_SUS_4, A_SHARP_SUS_4, B_SUS_4};
vector<vector<int>> SUS2_TRIADS {C_SUS_2, C_SHARP_SUS_2, D_SUS_2, D_SHARP_SUS_2, E_SUS_2, F_SUS_2, F_SHARP_SUS_2, G_SUS_2, G_SHARP_SUS_2, A_SUS_2, A_SHARP_SUS_2, B_SUS_2};


vector<vector<int>> MAJOR_SEVENTH_CHORDS {C_MAJOR_SEVENTH, C_SHARP_MAJOR_SEVENTH, D_MAJOR_SEVENTH, D_SHARP_MAJOR_SEVENTH, E_MAJOR_SEVENTH, F_MAJOR_SEVENTH, F_SHARP_MAJOR_SEVENTH, G_MAJOR_SEVENTH, G_SHARP_MAJOR_SEVENTH, A_MAJOR_SEVENTH, A_SHARP_MAJOR_SEVENTH, B_MAJOR_SEVENTH};
vector<vector<int>> MINOR_SEVENTH_CHORDS {C_MINOR_SEVENTH, C_SHARP_MINOR_SEVENTH, D_MINOR_SEVENTH, D_SHARP_MINOR_SEVENTH, E_MINOR_SEVENTH, F_MINOR_SEVENTH, F_SHARP_MINOR_SEVENTH, G_MINOR_SEVENTH, G_SHARP_MINOR_SEVENTH, A_MINOR_SEVENTH, A_SHARP_MINOR_SEVENTH, B_MINOR_SEVENTH};
vector<vector<int>> HALF_DIM_SEVENTH_CHORDS {C_HALF_DIM_SEVENTH, C_SHARP_HALF_DIM_SEVENTH, D_HALF_DIM_SEVENTH, D_SHARP_HALF_DIM_SEVENTH, E_HALF_DIM_SEVENTH, F_HALF_DIM_SEVENTH, F_SHARP_HALF_DIM_SEVENTH, G_HALF_DIM_SEVENTH, G_SHARP_HALF_DIM_SEVENTH, A_HALF_DIM_SEVENTH, A_SHARP_HALF_DIM_SEVENTH, B_HALF_DIM_SEVENTH};
vector<vector<int>> DOM_SEVENTH_CHORDS {C_DOM_SEVENTH, C_SHARP_DOM_SEVENTH, D_DOM_SEVENTH, D_SHARP_DOM_SEVENTH, E_DOM_SEVENTH, F_DOM_SEVENTH, F_SHARP_DOM_SEVENTH, G_DOM_SEVENTH, G_SHARP_DOM_SEVENTH, A_DOM_SEVENTH, A_SHARP_DOM_SEVENTH, B_DOM_SEVENTH};

vector<vector<int>> AUG_TRIADS {C_AUG, C_SHARP_AUG, D_AUG, D_SHARP_AUG};
vector<vector<int>> DIM_SEVENTH_CHORDS {C_DIM_SEVENTH, C_SHARP_DIM_SEVENTH, D_DIM_SEVENTH};


#endif
