/*
 * Copyright (C) 2011 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef LATINIME_PROXIMITY_INFO_H
#define LATINIME_PROXIMITY_INFO_H

#include <stdint.h>

#include "defines.h"

namespace latinime {

class Correction;

class ProximityInfo {
public:
    typedef enum {                             // Used as a return value for character comparison
        SAME_OR_ACCENTED_OR_CAPITALIZED_CHAR,  // Same char, possibly with different case or accent
        NEAR_PROXIMITY_CHAR,                   // It is a char located nearby on the keyboard
        UNRELATED_CHAR                         // It is an unrelated char
    } ProximityType;

    ProximityInfo(const int maxProximityCharsSize, const int keyboardWidth,
            const int keybaordHeight, const int gridWidth, const int gridHeight,
            const uint32_t *proximityCharsArray, const int keyCount, const int32_t *keyXCoordinates,
            const int32_t *keyYCoordinates, const int32_t *keyWidths, const int32_t *keyHeights,
            const int32_t *keyCharCodes, int themeId);
    ~ProximityInfo();
    bool hasSpaceProximity(const int x, const int y) const;
    void setInputParams(const int* inputCodes, const int inputLength);
    const int* getProximityCharsAt(const int index) const;
    unsigned short getPrimaryCharAt(const int index) const;
    bool existsCharInProximityAt(const int index, const int c) const;
    bool existsAdjacentProximityChars(const int index) const;
    ProximityType getMatchedProximityId(
            const int index, const unsigned short c, const bool checkProximityChars) const;
    bool sameAsTyped(const unsigned short *word, int length) const;
    const unsigned short* getPrimaryInputWord() const {
        return mPrimaryInputWord;
    }

private:
    // The max number of the keys in one keyboard layout
    static const int MAX_KEY_COUNT_IN_A_KEYBOARD = 64;
    // The upper limit of the char code in TOUCH_POSITION_CORRECTION_GROUP
    static const int MAX_GROUPED_CHAR_CODE = 127;

    int getStartIndexFromCoordinates(const int x, const int y) const;
    void initializeCodeToGroup();
    void initializeCodeToKeyIndex();
    const int MAX_PROXIMITY_CHARS_SIZE;
    const int KEYBOARD_WIDTH;
    const int KEYBOARD_HEIGHT;
    const int GRID_WIDTH;
    const int GRID_HEIGHT;
    const int CELL_WIDTH;
    const int CELL_HEIGHT;
    const int KEY_COUNT;
    const int THEME_ID;
    const int *mInputCodes;
    uint32_t *mProximityCharsArray;
    int32_t mKeyXCoordinates[MAX_KEY_COUNT_IN_A_KEYBOARD];
    int32_t mKeyYCoordinates[MAX_KEY_COUNT_IN_A_KEYBOARD];
    int32_t mKeyWidths[MAX_KEY_COUNT_IN_A_KEYBOARD];
    int32_t mKeyHeights[MAX_KEY_COUNT_IN_A_KEYBOARD];
    int32_t mKeyCharCodes[MAX_KEY_COUNT_IN_A_KEYBOARD];
    int mInputLength;
    unsigned short mPrimaryInputWord[MAX_WORD_LENGTH_INTERNAL];
    int mCodeToGroup[MAX_GROUPED_CHAR_CODE + 1];
    int mCodeToKeyIndex[MAX_GROUPED_CHAR_CODE + 1];
};

} // namespace latinime

#endif // LATINIME_PROXIMITY_INFO_H
