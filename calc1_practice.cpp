#include <algorithm>
#include <cctype>
#include <cmath>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

// Compile: g++ -std=c++17 -O2 calc1_practice.cpp -o calc1_practice
// All trigonometric angles are in radians. Answers use exact fractions.
struct Problem {
    std::string question, answer;
    std::vector<std::string> steps;
};

std::mt19937 rng(std::random_device{}());
int pick(int lo, int hi) {
    return std::uniform_int_distribution<int>(lo, hi)(rng);
}
std::string s(int n) { return std::to_string(n); }

Problem generate(int topic) {
    int a = pick(2, 7), b = pick(1, 8), n = pick(2, 5);
    switch (topic) {
    case 1: {
        int c = pick(1, 6);
        return {"Find lim as x -> " + s(c) + " of (x^2 - " + s(c*c) + ")/(x - " + s(c) + ").",
            s(2*c), {"Direct substitution gives 0/0, so simplify before evaluating.",
            "Factor the numerator: x^2 - " + s(c*c) + " = (x - " + s(c) + ")(x + " + s(c) + ").",
            "For x != " + s(c) + ", cancel the common factor. The expression becomes x + " + s(c) + ".",
            "Evaluate the simplified expression at x = " + s(c) + ": " + s(2*c) + "."}};
    }
    case 2:
        return {"Find lim as x -> 0 of sin(" + s(a) + "x)/(" + s(b) + "x).",
            s(a) + "/" + s(b), {"Use lim as u -> 0 of sin(u)/u = 1 (radians).",
            "Rewrite as (" + s(a) + "/" + s(b) + ") * sin(" + s(a) + "x)/(" + s(a) + "x).",
            "As x -> 0, u = " + s(a) + "x -> 0, so the second factor tends to 1.",
            "The limit is " + s(a) + "/" + s(b) + "."}};
    case 3:
        return {"Differentiate f(x) = " + s(a) + "x^" + s(n) + " + " + s(b) + "x - " + s(a+b) + ".",
            "f'(x) = " + s(a*n) + "x^" + s(n-1) + " + " + s(b),
            {"Differentiate each term separately.", "Power rule: d/dx [c*x^n] = c*n*x^(n-1).",
            "The first term becomes " + s(a*n) + "x^" + s(n-1) + ".",
            "The linear term becomes " + s(b) + ", and the constant becomes 0."}};
    case 4:
        return {"Differentiate f(x) = (" + s(a) + "x + " + s(b) + ")^" + s(n) + ".",
            "f'(x) = " + s(a*n) + "(" + s(a) + "x + " + s(b) + ")^" + s(n-1),
            {"Use the chain rule. Let u = " + s(a) + "x + " + s(b) + ".",
            "The outer derivative is n*u^(n-1); the inner derivative is " + s(a) + ".",
            "Multiply: " + s(n) + "(" + s(a) + "x + " + s(b) + ")^" + s(n-1) + " * " + s(a) + ".",
            "Combine the constant factors to get " + s(a*n) + "."}};
    case 5:
        return {"Differentiate f(x) = x^" + s(n) + " * sin(" + s(a) + "x).",
            "f'(x) = " + s(n) + "x^" + s(n-1) + "*sin(" + s(a) + "x) + " + s(a) + "x^" + s(n) + "*cos(" + s(a) + "x)",
            {"Use the product rule: (uv)' = u'v + uv'.",
            "Let u = x^" + s(n) + " and v = sin(" + s(a) + "x).",
            "Then u' = " + s(n) + "x^" + s(n-1) + " and v' = " + s(a) + "cos(" + s(a) + "x), by the chain rule.",
            "Substitute u, v, u', and v' into the product rule."}};
    case 6:
        return {"Differentiate f(x) = (" + s(a) + "x + " + s(b) + ")/(x + " + s(a) + ").",
            "f'(x) = " + s(a*a-b) + "/(x + " + s(a) + ")^2, x != -" + s(a),
            {"Use the quotient rule: (u/v)' = (u'v - uv')/v^2.",
            "Here u' = " + s(a) + " and v' = 1.",
            "The numerator is " + s(a) + "(x + " + s(a) + ") - (" + s(a) + "x + " + s(b) + ").",
            "The x terms cancel, leaving " + s(a*a-b) + ". Keep the original restriction x != -" + s(a) + "."}};
    case 7:
        return {"Differentiate f(x) = " + s(b) + "e^(" + s(a) + "x) + ln(x), for x > 0.",
            "f'(x) = " + s(a*b) + "e^(" + s(a) + "x) + 1/x",
            {"Use d/dx [e^u] = e^u * u'.", "For u = " + s(a) + "x, u' = " + s(a) + ".",
            "Thus the exponential term has derivative " + s(a*b) + "e^(" + s(a) + "x).",
            "Add d/dx [ln(x)] = 1/x."}};
    case 8:
        return {"For x^2 + y^2 = " + s(a*a+b*b) + ", find dy/dx at (" + s(a) + ", " + s(b) + ").",
            "dy/dx = -" + s(a) + "/" + s(b),
            {"Differentiate both sides with respect to x, treating y as a function of x.",
            "This gives 2x + 2y*(dy/dx) = 0.", "Solve: dy/dx = -x/y, when y != 0.",
            "Substitute the given point: -" + s(a) + "/" + s(b) + "."}};
    case 9:
        return {"Find the tangent line to y = x^2 + " + s(b) + " at x = " + s(a) + ".",
            "y - " + s(a*a+b) + " = " + s(2*a) + "(x - " + s(a) + ")",
            {"Evaluate the function: the point is (" + s(a) + ", " + s(a*a+b) + ").",
            "Differentiate: y' = 2x.", "At x = " + s(a) + ", the slope is " + s(2*a) + ".",
            "Use point-slope form: y - y0 = m(x - x0)."}};
    case 10:
        return {"Find the critical point and classify it for f(x) = x^2 - " + s(2*a) + "x + " + s(b) + ".",
            "Minimum at (" + s(a) + ", " + s(b-a*a) + "); no maximum on the real line.",
            {"Differentiate: f'(x) = 2x - " + s(2*a) + ".",
            "Set f'(x) = 0 to get x = " + s(a) + ". The derivative exists everywhere.",
            "The second derivative is 2 > 0, so this is a local minimum.",
            "Complete the square: f(x) = (x - " + s(a) + ")^2 + (" + s(b-a*a) + ").",
            "The square is nonnegative and grows without bound, so this is also the global minimum and there is no maximum."}};
    case 11: {
        int perimeter = 4*a;
        return {"A rectangle has perimeter " + s(perimeter) + ". What dimensions maximize its area?",
            s(a) + " by " + s(a) + "; maximum area = " + s(a*a),
            {"Let the sides be x and y. Then 2x + 2y = " + s(perimeter) + ", so y = " + s(2*a) + " - x.",
            "Area A(x) = x(" + s(2*a) + " - x), with 0 < x < " + s(2*a) + ".",
            "A'(x) = " + s(2*a) + " - 2x. Set this to zero: x = " + s(a) + ".",
            "A''(x) = -2 < 0 throughout the domain, so the critical point gives the global maximum.",
            "Then y = " + s(a) + ", and area = " + s(a*a) + "."}};
    }
    case 12:
        return {"Find the indefinite integral of (" + s(a) + "x^" + s(n) + " + " + s(b) + ") dx.",
            "(" + s(a) + "/" + s(n+1) + ")x^" + s(n+1) + " + " + s(b) + "x + C",
            {"Integrate each term separately.", "Power rule: integral x^n dx = x^(n+1)/(n+1) + C, for n != -1.",
            "The polynomial term integrates to (" + s(a) + "/" + s(n+1) + ")x^" + s(n+1) + ".",
            "The constant integrates to " + s(b) + "x. Include an arbitrary constant C."}};
    case 13:
        return {"Evaluate the definite integral from 0 to " + s(b) + " of " + s(a) + "x dx.",
            s(a*b*b) + "/2",
            {"An antiderivative is F(x) = (" + s(a) + "/2)x^2.",
            "By the Fundamental Theorem of Calculus, the integral is F(" + s(b) + ") - F(0).",
            "Substitute the endpoints: (" + s(a) + "/2)*" + s(b*b) + " - 0 = " + s(a*b*b) + "/2."}};
    case 14:
        return {"Find the indefinite integral of " + s(2*a) + "x*(" + s(a) + "x^2 + " + s(b) + ")^" + s(n) + " dx.",
            "(" + s(a) + "x^2 + " + s(b) + ")^" + s(n+1) + "/" + s(n+1) + " + C",
            {"Substitute u = " + s(a) + "x^2 + " + s(b) + ", so du = " + s(2*a) + "x dx.",
            "The integral becomes integral u^" + s(n) + " du.",
            "Apply the power rule to get u^" + s(n+1) + "/" + s(n+1) + " + C.",
            "Substitute the expression for u back into the answer."}};
    default:
        return {"Find d/dx of the integral from 0 to x^" + s(n) + " of (t^2 + " + s(b) + ") dt.",
            "(x^" + s(2*n) + " + " + s(b) + ") * " + s(n) + "x^" + s(n-1),
            {"Use the Fundamental Theorem of Calculus with the chain rule.",
            "For integral from 0 to g(x) of f(t) dt, the derivative is f(g(x))*g'(x), since f is continuous.",
            "Here g(x) = x^" + s(n) + ", so g'(x) = " + s(n) + "x^" + s(n-1) + ".",
            "Substitute t = x^" + s(n) + " into t^2 + " + s(b) + ", then multiply by g'(x)."}};
    }
}

const std::vector<std::string> topics = {
    "Mixed practice", "Limits: factoring", "Limits: trigonometry",
    "Derivatives: power rule", "Derivatives: chain rule", "Derivatives: product rule",
    "Derivatives: quotient rule", "Derivatives: exponential and logarithmic",
    "Implicit differentiation", "Tangent lines", "Critical points and extrema",
    "Optimization", "Indefinite integrals", "Definite integrals",
    "Integration by substitution", "Fundamental Theorem + chain rule"
};

std::string command(std::string line) {
    std::transform(line.begin(), line.end(), line.begin(),
        [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    std::istringstream input(line);
    std::string word;
    input >> word;
    return word;
}

int main() {
    std::cout << "CALCULUS 1 PRACTICE\n"
              << "Work on paper, then request an answer or steps. No automatic grading.\n"
              << "Angles are in radians; fractions may be unreduced.\n";
    int count = 0;
    while (true) {
        std::cout << "\nTOPICS\n";
        for (std::size_t i = 0; i < topics.size(); ++i)
            std::cout << i << ") " << topics[i] << '\n';
        std::cout << "Choose 0-15, or q to quit: ";
        std::string line;
        if (!std::getline(std::cin, line) || command(line) == "q" || command(line) == "quit") break;
        std::istringstream choice(line);
        int selected;
        std::string extra;
        if (!(choice >> selected) || (choice >> extra) || selected < 0 || selected > 15) {
            std::cout << "Please enter one topic number from 0 to 15.\n";
            continue;
        }
        bool menu = false;
        while (!menu) {
            int topic = selected == 0 ? pick(1, 15) : selected;
            Problem p = generate(topic);
            std::size_t step = 0;
            std::cout << "\nProblem " << ++count << " - " << topics[topic] << "\n" << p.question << '\n';
            while (true) {
                std::cout << "\n[a] answer  [h] next step  [s] full solution  [n] next problem  [m] menu  [q] quit\n> ";
                if (!std::getline(std::cin, line)) return 0;
                std::string c = command(line);
                if (c == "q" || c == "quit") { std::cout << "Goodbye!\n"; return 0; }
                if (c == "m" || c == "menu") { menu = true; break; }
                if (c == "n" || c == "next") break;
                if (c == "a" || c == "answer") std::cout << "Answer: " << p.answer << '\n';
                else if (c == "h" || c == "hint") {
                    if (step < p.steps.size()) {
                        std::cout << "Step " << step+1 << ": " << p.steps[step] << '\n';
                        ++step;
                    } else std::cout << "All steps shown. Answer: " << p.answer << '\n';
                } else if (c == "s" || c == "steps" || c == "solution") {
                    for (std::size_t i = 0; i < p.steps.size(); ++i)
                        std::cout << i+1 << ". " << p.steps[i] << '\n';
                    step = p.steps.size();
                    std::cout << "Answer: " << p.answer << '\n';
                } else std::cout << "Use a, h, s, n, m, or q.\n";
            }
        }
    }
    std::cout << "Goodbye!\n";
    return 0;
}
