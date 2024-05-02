;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; readtsc.asm: Read Time Stamp Counter (TSC) on x64 processors (for MASM).  ;;
;; This file is part of PedCom64, a X64 library for EC Pedersen commitments. ;;
;; Project repository: <http://bitbucket.org/christian_franck/pedcomlib/>.   ;;
;; Version 0.8.0 (2018-04-20), see project repository for latest version.    ;;
;; Authors: C. Franck and J. Groszschaedl (SnT, University of Luxembourg).   ;;
;; License: GPLv3 (see LICENSE file), other licenses available upon request. ;;
;; Copyright (C) 2016-2017 University of Luxembourg <http://www.uni.lu/>.    ;;
;; ------------------------------------------------------------------------- ;;
;; This program is free software: you can redistribute it and/or modify it   ;;
;; under the terms of the GNU General Public License as published by the     ;;
;; Free Software Foundation, either version 3 of the License, or (at your    ;;
;; option) any later version. This program is distributed in the hope that   ;;
;; it will be useful, but WITHOUT ANY WARRANTY; without even the implied     ;;
;; warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the  ;;
;; GNU General Public License for more details. You should have received a   ;;
;; copy of the GNU General Public License along with this program. If not,   ;;
;; see <http://www.gnu.org/licenses/>.                                       ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;; Function prototype:
;; -------------------
;; uint64_t read_tsc(void);
;; 
;; Parameters:
;; -----------
;; None.
;; 
;; Return value:
;; -------------
;; The value of the time-stamp counter as a 64-bit unsigned integer.
;; 
;; Description:
;; ------------
;; The function read_tsc returns the value of the Time Stamp Counter (TSC)
;; register, which counts the number of clock cycles elapsed since the last
;; reset. It can be used to determine the execution time a piece of code takes
;; by simply calling read_tsc before and after the code to measure and then
;; calculating the difference. Note, however, that the red_tsc function itself
;; can, depending on the target processor, take several hundred clock cycles,
;; which must be considered when calculating the execution time. In addition,
;; it should be taken into account that the number of clock cycles may not be
;; (fully) reproducible on some older X64 processors with non-invariant TSC
;; behavior (see http://oliveryang.net/2015/09/pitfalls-of-TSC-usage). This
;; implementation of the read_tsc function is based on Agner Fog's asmlib (see
;; http://www.agner.org/optimize/#asmlib).


option casemap:none         ;; make internal symbol recognition case-sensitive
option prologue:none        ;; prevent MASM from generating standard prologue
option epilogue:none        ;; prevent MASM from generating standard epilogue
.code                       ;; place current section in code segment


read_tsc proto              ;; read_tsc does not expect parameters on the stack


read_tsc proc
    push    rbx             ;; ebx gets modified by cpuid
    xor     eax, eax        ;; set eax to 0
    cpuid                   ;; serialize instruction execution
    rdtsc                   ;; read out TSC and place it in edx:eax
    shl     rdx, 32         ;; edx holds the upper 32 bits of 64-bit TSC value
    or      rax, rdx        ;; combine upper & lower 32 bits in 64-bit reg rax
    push    rax             ;; push rax on stack
    xor     eax, eax        ;; set eax to 0
    cpuid                   ;; serialize instruction execution
    pop     rax             ;; restore rax (holds return value)
    pop     rbx             ;; restore rbx
    ret                     ;; return to caller
read_tsc endp


end
