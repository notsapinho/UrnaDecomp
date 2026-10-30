# ecourna::api::exception::CBaseError<E, Limites>'s constructor: target fn 1011, binaryen's merge of 13 ecourna
# instantiations, fn 710, the merge of the instantiations compiled with uenux2's flags, and the thunks that pass each
# one's vptr. The unit is a form of two headers and has no source or companion of its own: CError's template constructor
# in src/ecourna/api/exception/cerror.hpp, which CBaseError's constructor in cbaseerror.hpp calls. Every TU that throws
# a CBaseError emits this code, so most matches come from the landed objects of both trees; 346 and 1889 come from
# app/roots_uenux2.o and 1229 from app/75-uenux2-api-hwil-roots.o, whose bodies compile the same at the tree's flags.
#
# Matches: 1011 and its thunks 9025 9026 9041 9046 9107 9158 9181 9229 9266 9410 9461 9505 9584; 710 and its thunks 253
# 346 406 480 655 1229 1715 1889 2260, 480 once unit 95 gives its enum, 1715 and 2260 once units 66 and 91 throw them.
# Bodies of units 06 and 07 that were `unresolved self-voted` on those thunks match with them:
# 9539 (CZip, on 9584), 9028 (CConfiguracaoMunicipios, on 9026), 9047 (CFederacao, on 9046).
#
# Evidence for the form. 1011 and 710 read and zero both words of the moved string, then store them into the frame
# temporary, last word first (+12, +4): docs/reference/facts/codegen.md §C1, values read first are stored in reverse, so
# the string is moved twice. 2294, the target's copy from the executable TU (-Oz -fexceptions, facts/levels.md §V1),
# shows the second move out of line: its five thunks (170 210 235 255 331) store the vptr after an invoke through a slot
# each passes, 469 483 159 477 144, and all five slots are one function, 2379 (`wasm-objdump -x -j Elem
# target/vota_web_wasm.wasm | /usr/bin/grep -c 'ref.func:2379$'` prints 5, the five symbols binaryen merged). 2379 moves
# the string, invokes slot 169 (CError's constructor, fn 1143) and stores no vptr. So one function per enum sits between
# the two constructors and sets no vptr, which is a delegating constructor of CError.
#
# Measured on `template class CBaseError<EProbe, SErrorLimits{1, 2}>`, one header per form, at ecourna's flags,
# uenux2's, and -Oz -fexceptions, comparing each function with the object's numbers masked (how-to step 3):
#   - as landed: 1011's store order at ecourna's flags (read and zero, __THREW__ cleared, +12, +4), 710's at uenux2's.
#     clang inlines the template constructor there: neither object defines it. At -Oz it stays out of line with 2379's
#     rows, and CBaseError's has 2294's.
#   - the same functions at all three flag sets: the template constructor defined after the class with `inline`. In the
#     class is chosen. Also chosen, no byte decides them: the template head (the five slots show one function per enum,
#     no more), `static_cast<int>` for the conversion, and public access.
#   - the template constructor taking `const std::source_location&`, `const E&` or `E&&`: 1011's and 710's bytes, but at
#     -Oz CBaseError's stores the parameter into its frame and the template constructor reloads it, and 2294 passes p1
#     and p3 straight to 2379, which reads neither from memory. So those two parameters by value are evidence.
#   - a by-value parameter with no template constructor (the form before this unit), or a template constructor taking
#     `std::string&&`: one move, the temporary 8-aligned at +0 and stored as it is read, not 1011's or 710's order.
#   - CBaseError delegating to a constructor of its own: 1011's and 710's bytes, but at -Oz the vptr store moves into
#     the inner function, and 2379 has none while 2294 has one.
#   - an intermediate class template over CError: 1011's and 710's bytes, but its constructor stores a vptr, which 2379
#     does not, and the RTTI of all 44 CBaseError instantiations in ledger/classes.json names CError as the direct base.
#   - CBaseError taking `std::string&&`: the constructor's bytes, but its callers' frames shrink by 16 B (api::truncate
#     480 B against 496 B), which drifts matched 5457, 2759 and 5498. So the by-value parameter is evidence.
#
# Left as they are. 1074 (CBaseError<EApiAsnError, {1900, 1910}>) is written and `differs`: the target's copy is
# uenux2's, on 710, and all nine target callers are unwritten, so ours comes from ecourna objects, on 1011. With one
# uenux2-flags instantiation first in a clone of the objects (facts/workflow.md §W13) its body scores 2 over 8 rows,
# both operands, the vptr and the call into the 710 body: it waits for its first uenux2 caller. 170 210 235 255 331 wait
# for the executable TU, src/uenux2/wasm/vota_web/vota_web_wasm.cpp, since ours are uenux2's copies (210: target
# `i32.const 483`, ours `call 710`). 1143, CError's constructor, is 787 rows with 67 operand-only, and stops on the name
# of 296, std::to_string(int), which equals our body up to callees.
