CALCULUS I - EXAM PRACTICE EDITION

QUICK START (Windows)
1. Extract Calc1-Exam-Practice.zip into a folder.
2. Double-click calc1_exam.exe.
3. Choose a topic and a difficulty in the browser window.
4. Click Exit app when finished, then close the tab.

Keep exam_gui.html beside calc1_exam.exe. No installation, internet access,
LaTeX installation, or external math library is needed. Use a modern browser
with native MathML support, such as Edge, Chrome, or Firefox.
Closing only the browser tab leaves the local C++ program running.

WHAT CHANGED
- 40 original problem families across 20 topics, with randomized values.
- Standard Exam, Challenge, and Mixed Exam Levels.
- Mixed-topic mode avoids repeating the same topic consecutively.
- Mixed levels alternate when practicing one topic.
- Immediate identical questions are avoided.
- Solutions have 5-7 numbered explanation cards: strategy, algebra,
  typeset equations, selected mistake callouts, and a final check.
- A progress indicator, collapsible steps, and separate answer reveal.

EXAM TOPICS
Algebraic, radical, infinite and trigonometric limits; derivative rules;
higher and implicit derivatives; logarithmic differentiation; tangent and
normal lines; extrema and concavity; optimization; indefinite and definite
integrals; area versus signed integral; substitution; FTC with variable
bounds; ladder and cone related rates; continuity and differentiability;
Mean Value Theorem; linear approximation; initial-value and motion problems;
and L'Hopital's rule.

These are original practice problems based on common Calc I skills, not
questions taken from a particular school or a prediction of your exam.
The difficulty labels describe this bank. Course coverage and difficulty vary.
Angles are in radians. Work on paper: the app does not grade answers.

BUTTONS
Show answer: reveal the answer without revealing the solution steps.
Show next step: reveal one card of reasoning.
Full solution: reveal all cards, the answer, and the check.
Collapse/Expand steps: hide or redisplay already revealed steps.
Next problem: clear the solution and generate a fresh question.

SOURCE FILES
calc1_gui.cpp       C++ Windows launcher, local HTTP server, JSON responses.
exam_bank.h         Expanded bank and detailed solution templates.
exam_gui.html      Offline browser interface and native MathML renderer.
calc1_practice.cpp Shared helpers and the original terminal program.

BUILD (Windows, GCC / MinGW with C++17)
g++ -std=c++17 -O2 -Wall -Wextra -static -mwindows calc1_gui.cpp -o calc1_exam.exe -lws2_32 -lshell32

The GUI is Windows-specific. The C++ process serves the interface only on
127.0.0.1, on a dynamically selected port with a random session URL.

VALIDATION
Compiled with GCC and warnings enabled. Exercised 480 generated problems
covering all 40 families. Independent numerical checks covered derivatives,
integrals, limits, optimization, motion, related rates and theorem results.
Checked answer-only reveal, progressive steps, completion, collapse, reset,
and request-failure behavior; validated 3,384 rendered MathML expressions.
Live browser visual checks were blocked by the browser tool's URL check.
End-to-end HTTP client testing was blocked by the execution environment's
local socket access restrictions.
