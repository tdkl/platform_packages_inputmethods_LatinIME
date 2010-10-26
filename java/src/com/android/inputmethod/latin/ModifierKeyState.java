/*
 * Copyright (C) 2010 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */

package com.android.inputmethod.latin;

class ModifierKeyState {
    private static final int RELEASING = 0;
    private static final int PRESSING = 1;
    private static final int PRESSING_ON_SHIFTED = 2; // both temporary shifted & shift locked
    private static final int MOMENTARY = 3;
    private static final int IGNORING = 4;

    private int mState = RELEASING;

    public void onPress() {
        mState = PRESSING;
    }

    public void onPressOnShifted() {
        mState = PRESSING_ON_SHIFTED;
    }

    public void onRelease() {
        mState = RELEASING;
    }

    public void onOtherKeyPressed() {
        if (mState == PRESSING) {
            mState = MOMENTARY;
        } else if (mState == PRESSING_ON_SHIFTED) {
            mState = IGNORING;
        }
    }

    public boolean isMomentary() {
        return mState == MOMENTARY;
    }

    public boolean isPressingOnShifted() {
        return mState == PRESSING_ON_SHIFTED;
    }

    public boolean isIgnoring() {
        return mState == IGNORING;
    }
}
