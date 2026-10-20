#pragma once
#include <numeric>
#include <stdexcept>
struct ExamStep { std::string title, why, math, tip; };
struct ExamProblem {
    std::string id, prompt, math, answer, conclusion, check;
    std::vector<ExamStep> steps;
    int topic=0, level=1;
};
const std::vector<std::string> examTopics = {
    "Mixed exam practice", "Limits: algebra and infinity", "Limits: trigonometry",
    "Derivatives and higher derivatives", "Chain rule and nested functions",
    "Product rule", "Quotient rule", "Exponential and logarithmic derivatives",
    "Implicit differentiation", "Tangent and normal lines", "Curve analysis and extrema",
    "Optimization", "Indefinite integrals", "Definite integrals and area",
    "Integration by substitution", "Fundamental Theorem of Calculus", "Related rates",
    "Continuity and differentiability", "Mean Value Theorem and linear approximation",
    "Motion and initial-value problems", "L'Hopital's rule and indeterminate forms"
};
std::string fraction(long long a,long long b) {
    if(b<0){a=-a;b=-b;}long long g=std::gcd(a,b);a/=g;b/=g;
    return b==1?std::to_string(a):"("+std::to_string(a)+")/("+std::to_string(b)+")";
}
ExamProblem examProblem(int topic,int level) {
    int a=pick(2,5),b=pick(2,6),c=pick(1,4);
    std::string A=s(a),B=s(b),C=s(c);
    ExamProblem p;p.topic=topic;p.level=level;p.id=s(topic)+"-"+s(level);
    auto add=[&](std::string title,std::string why,std::string math="",std::string tip=""){
        p.steps.push_back({title,why,math,tip});
    };
    if(topic==1&&level==1){
        p.prompt="Evaluate without L'Hopital's rule.";
        p.math="LIM[x|0|(sqrt("+s(a*a)+"+x)-"+A+")/x]";
        p.answer="1/"+s(2*a);
        add("Recognize the form","Direct substitution gives 0/0, an indeterminate form. Simplify before evaluating.");
        add("Choose the conjugate","Multiply numerator and denominator by the expression with the opposite sign.","sqrt("+s(a*a)+"+x)+"+A);
        add("Rationalize","Use the difference of two squares to remove the radical from the numerator.","(("+s(a*a)+"+x)-"+s(a*a)+")/(x*(sqrt("+s(a*a)+"+x)+"+A+"))");
        add("Cancel a common factor","For nonzero x, cancel x. A limit concerns nearby values, so this is valid.","1/(sqrt("+s(a*a)+"+x)+"+A+")","Cancel factors, not terms separated by addition.");
        add("Evaluate the new expression","The denominator now approaches a positive nonzero value.","1/("+A+"+"+A+") = "+p.answer);
        p.check="The expression is positive near zero, consistent with the positive answer.";
    }else if(topic==1){
        p.prompt="Evaluate at negative infinity. Pay attention to the sign of the radical.";
        p.math="LIM[x|-infinity|(sqrt("+s(a*a)+"x^2+"+B+")+"+C+"x)/("+B+"x-1)]";
        p.answer=fraction(c-a,b);
        add("Identify the dominant powers","Both numerator and denominator scale like the magnitude of x.");
        add("Factor inside the radical","The square root of x squared is its absolute value.","sqrt("+s(a*a)+"x^2+"+B+") = abs(x)*sqrt("+s(a*a)+"+"+B+"/x^2)","sqrt(x^2) equals |x|, not always x.");
        add("Use the direction of the limit","For negative x, the absolute value equals negative x.","abs(x) = -x");
        add("Divide by x","Divide the entire numerator and denominator by x.","(-sqrt("+s(a*a)+"+"+B+"/x^2)+"+C+")/("+B+"-1/x)");
        add("Take the limit","Inverse powers of x tend to zero.","(-"+A+"+"+C+")/"+B+" = "+p.answer);
        p.check="For large negative x, the radical behaves like -"+A+"x. The leading-term ratio agrees.";
    }else if(topic==2&&level==1){
        p.prompt="Evaluate using trigonometric identities and fundamental limits, without L'Hopital's rule.";
        p.math="LIM[x|0|(1-cos("+A+"x))/x^2]";p.answer=fraction(a*a,2);
        add("Recognize the form","Substitution gives 0/0; rewrite the numerator.");
        add("Use a half-angle identity","One minus cosine is twice a squared sine.","1-cos("+A+"x) = 2*sin(("+A+"/2)*x)^2");
        add("Build a standard sine ratio","Insert the inner angle in the denominator and compensate by a constant.","("+s(a*a)+"/2)*(sin(("+A+"/2)*x)/(("+A+"/2)*x))^2");
        add("Apply the fundamental limit","In radians, sin(u)/u tends to one as u approaches zero.","LIM[u|0|sin(u)/u] = 1","The coefficient must be squared along with the ratio.");
        add("Evaluate","Only the constant factor remains.",p.answer);
        p.check="Both the numerator and denominator are nonnegative near zero.";
    }else if(topic==2){
        p.prompt="Evaluate using identities and the fundamental sine limit.";
        p.math="LIM[x|0|(tan("+A+"x)-sin("+A+"x))/x^3]";p.answer=fraction(a*a*a,2);
        add("Rewrite tangent","Express tangent as sine divided by cosine, then factor sine.","tan("+A+"x)-sin("+A+"x) = sin("+A+"x)*(1-cos("+A+"x))/cos("+A+"x)");
        add("Separate the denominator","Split x cubed into x times x squared.","(sin("+A+"x)/x)*((1-cos("+A+"x))/x^2)*(1/cos("+A+"x))");
        add("Evaluate the sine factor","Compensate for the inner coefficient.","LIM[x|0|sin("+A+"x)/x] = "+A);
        add("Evaluate the cosine-difference factor","Use the half-angle identity and the squared sine limit.","LIM[x|0|(1-cos("+A+"x))/x^2] = "+fraction(a*a,2));
        add("Multiply the limits","The reciprocal cosine factor tends to one.",A+"*("+fraction(a*a,2)+")*1 = "+p.answer);
        p.check="The numerator is cubic in size near zero, consistent with a finite limit.";
    }else if(topic==3&&level==1){
        p.prompt="Find the first derivative. Rewrite radicals and reciprocals as powers first. Assume x > 0.";
        p.math="f(x) = "+A+"x^4-"+B+"sqrt(x)+"+C+"/x^2";
        p.answer="f'(x) = "+s(4*a)+"x^3-"+B+"/(2*sqrt(x))-"+s(2*c)+"/x^3";
        add("Rewrite as powers","Use fractional and negative exponents.","f(x) = "+A+"x^4-"+B+"x^(1/2)+"+C+"x^(-2)");
        add("State the rule","Multiply by the old exponent, then subtract one from that exponent.","DERIV[x^n] = n*x^(n-1)");
        add("Differentiate the polynomial","Keep its constant coefficient.","DERIV["+A+"x^4] = "+s(4*a)+"x^3");
        add("Differentiate the radical","The new exponent is negative one half.","DERIV[-"+B+"x^(1/2)] = -("+B+"/2)*x^(-1/2)");
        add("Differentiate the reciprocal","The negative exponent also makes the coefficient negative.","DERIV["+C+"x^(-2)] = -"+s(2*c)+"x^(-3)","The new exponent is -3, not -1.");
        add("Combine and rewrite","Convert the negative powers to fractions.",p.answer);
        p.check="All terms and their derivatives are defined for x > 0.";
    }else if(topic==3){
        p.prompt="Find the second derivative and state the original function's domain.";
        p.math="f(x) = "+A+"x^3*ln(x)";p.answer="f''(x) = "+s(6*a)+"x*ln(x)+"+s(5*a)+"x";p.conclusion="Domain: x > 0.";
        add("Check the domain","A real logarithm requires a positive argument.","x > 0");
        add("Differentiate once","Apply the product rule to the polynomial and logarithm.","f'(x) = "+s(3*a)+"x^2*ln(x)+"+A+"x^2");
        add("Differentiate the product again","The first term still needs a product rule.","DERIV["+s(3*a)+"x^2*ln(x)] = "+s(6*a)+"x*ln(x)+"+s(3*a)+"x");
        add("Differentiate the remaining term","Do not omit the second term of the first derivative.","DERIV["+A+"x^2] = "+s(2*a)+"x");
        add("Combine like terms","Add the two linear terms.",p.answer,"A second derivative differentiates the complete first derivative.");
        p.check="Both derivatives have the same positive-x domain.";
    }else if(topic==4&&level==1){
        p.prompt="Differentiate the nested function. Leave your answer factored.";
        p.math="f(x) = sin("+A+"x^2+"+B+")^3";
        p.answer="f'(x) = "+s(6*a)+"x*sin("+A+"x^2+"+B+")^2*cos("+A+"x^2+"+B+")";
        add("Identify three layers","From outside inward: cube, sine, quadratic.","u = "+A+"x^2+"+B);
        add("Differentiate the cube","Keep the inner expression intact.","DERIV[sin(u)^3] = 3*sin(u)^2*cos(u)*u'");
        add("Differentiate the innermost expression","The constant vanishes.","u' = "+s(2*a)+"x");
        add("Multiply all chain factors","Each layer contributes one derivative factor.","f'(x) = 3*sin(u)^2*cos(u)*"+s(2*a)+"x","Do not omit the quadratic's derivative.");
        add("Substitute and simplify","Replace u and combine the constants.",p.answer);
        p.check="The derivative includes a cosine from the sine layer and an x factor from the quadratic.";
    }else if(topic==4){
        p.prompt="Differentiate the nested exponential. State where the derivative formula is valid.";
        p.math="f(x) = e^(sqrt(1+"+A+"*ln(x)))";
        p.answer="f'(x) = ("+A+"*e^(sqrt(1+"+A+"*ln(x))))/(2*x*sqrt(1+"+A+"*ln(x)))";
        p.conclusion="Original domain: x >= e^(-1/"+A+"). Derivative formula valid for x > e^(-1/"+A+").";
        add("Check the domain","The logarithm needs positive x and the square-root radicand must be nonnegative.","1+"+A+"*ln(x) >= 0");
        add("Name the inner function","The outer exponential differentiates to itself times the inner derivative.","u = sqrt(1+"+A+"*ln(x))");
        add("Differentiate the square root","Divide the radicand's derivative by twice its square root.","u' = ("+A+"/x)/(2*sqrt(1+"+A+"*ln(x)))");
        add("Multiply by the exponential","Include the logarithm's derivative and the constant coefficient.",p.answer);
        add("Restrict to the interior","The denominator vanishes at the original domain's endpoint.","x > e^(-1/"+A+")","A function can exist at an endpoint without having a finite derivative there.");
        p.check="Exponential, square-root, logarithm and linear-coefficient factors all appear.";
    }else if(topic==5&&level==1){
        p.prompt="Differentiate. Assume x > 0.";
        p.math="f(x) = (x^2+"+A+")*ln(x)";
        p.answer="f'(x) = 2*x*ln(x)+(x^2+"+A+")/x";
        add("Choose the product rule","There are two nonconstant factors.","DERIV[u*v] = u'*v+u*v'");
        add("Label the factors","Keep track of which factor is differentiated in each term.","u = x^2+"+A+", v = ln(x)");
        add("Find their derivatives","Use the power rule and logarithm derivative.","u' = 2*x, v' = 1/x");
        add("Assemble both terms","Differentiate only one factor in each term.","f'(x) = 2*x*ln(x)+(x^2+"+A+")*(1/x)","The product of the derivatives is not the derivative of the product.");
        add("Write the final form","The second product becomes a quotient.",p.answer);
        p.check="Expanding the second term as x + "+A+"/x gives an equivalent answer.";
    }else if(topic==5){
        p.prompt="Differentiate the product of three functions. Factor out the exponential.";
        p.math="f(x) = x^2*e^("+A+"x)*cos("+B+"x)";
        p.answer="f'(x) = e^("+A+"x)*((2*x+"+A+"x^2)*cos("+B+"x)-"+B+"x^2*sin("+B+"x))";
        add("Use a three-factor product rule","Differentiate one factor at a time.","DERIV[u*v*w] = u'*v*w+u*v'*w+u*v*w'");
        add("Differentiate the polynomial","The other two factors stay unchanged in this contribution.","DERIV[x^2] = 2*x");
        add("Differentiate the exponential","Apply the chain rule to its exponent.","DERIV[e^("+A+"x)] = "+A+"*e^("+A+"x)");
        add("Differentiate cosine","Retain both the minus sign and the inner coefficient.","DERIV[cos("+B+"x)] = -"+B+"*sin("+B+"x)");
        add("Assemble three contributions","All terms share the same exponential.","f'(x) = 2*x*e^("+A+"x)*cos("+B+"x)+"+A+"x^2*e^("+A+"x)*cos("+B+"x)-"+B+"x^2*e^("+A+"x)*sin("+B+"x)");
        add("Factor and collect","Group the two cosine contributions.",p.answer);
        p.check="Before factoring, there must be three contributions, including one negative sine term.";
    }else if(topic==6&&level==1){
        p.prompt="Differentiate the quotient. Leave the denominator squared.";
        p.math="f(x) = sin("+A+"x)/(x^2+"+B+")";
        p.answer="f'(x) = ("+A+"*cos("+A+"x)*(x^2+"+B+")-2*x*sin("+A+"x))/(x^2+"+B+")^2";
        add("Choose the quotient rule","The denominator depends on x.","DERIV[u/v] = (u'*v-u*v')/v^2");
        add("Differentiate the numerator","Apply the chain rule.","u' = "+A+"*cos("+A+"x)");
        add("Differentiate the denominator","The constant drops out.","v' = 2*x");
        add("Substitute in order","Keep the full second product subtracted.",p.answer,"The numerator is u'v minus uv', not the reverse.");
        add("Check the domain","The original denominator is strictly positive for all real x.","x^2+"+B+" > 0");
        p.check="At x = 0 the derivative equals "+fraction(a,b)+", consistent with the original function's small-angle behavior.";
    }else if(topic==6){
        p.prompt="Differentiate and state all domain restrictions.";
        p.math="f(x) = ln(x)/(x^2-"+s(a*a)+")";
        p.answer="f'(x) = ((x^2-"+s(a*a)+")/x-2*x*ln(x))/(x^2-"+s(a*a)+")^2";
        p.conclusion="Domain: x > 0 and x != "+A+".";
        add("Find the original domain","The logarithm requires positive x; the denominator must also be nonzero.","x > 0, x != "+A);
        add("Differentiate both parts","Use the logarithm derivative and power rule.","u' = 1/x, v' = 2*x");
        add("Apply the quotient rule","Subtract the second product as a whole.","f'(x) = ((1/x)*(x^2-"+s(a*a)+")-ln(x)*2*x)/(x^2-"+s(a*a)+")^2");
        add("Clean up the numerator","Keep the squared denominator factored.",p.answer);
        add("Carry the restrictions forward","A derivative expression does not restore points missing from the original function.","x > 0, x != "+A,"Always check the logarithm and the denominator separately.");
        p.check="The numerator can also be written as x - "+s(a*a)+"/x - 2x ln(x).";
    }else if(topic==7&&level==1){
        p.prompt="Differentiate, simplifying with logarithm properties first.";
        p.math="f(x) = ln((x^2+"+A+")^3/sqrt(x))";
        p.answer="f'(x) = 6*x/(x^2+"+A+")-1/(2*x)";p.conclusion="Domain: x > 0.";
        add("Check the logarithm argument","The numerator is positive, and the square root is in the denominator.","x > 0");
        add("Expand the logarithm","Quotients become differences; powers become coefficients.","f(x) = 3*ln(x^2+"+A+")-(1/2)*ln(x)");
        add("Differentiate the first term","For ln(u), use u'/u.","DERIV[3*ln(x^2+"+A+")] = 6*x/(x^2+"+A+")");
        add("Differentiate the second term","Keep the coefficient and its sign.","DERIV[-(1/2)*ln(x)] = -1/(2*x)");
        add("Combine","A single common denominator is optional.",p.answer);
        p.check="Check domain restrictions in the original logarithm, before simplifying.";
    }else if(topic==7){
        p.prompt="Use logarithmic differentiation to find dy/dx. Assume x > 0.";
        p.math="y = x^("+A+"x)";p.answer="y' = "+A+"*x^("+A+"x)*(ln(x)+1)";
        add("Recognize the variable exponent","The base and exponent both depend on x, so the ordinary power rule alone does not apply.");
        add("Take logarithms","Use the log power rule; y is positive for x > 0.","ln(y) = "+A+"x*ln(x)");
        add("Differentiate implicitly","Use the chain rule on the left and product rule on the right.","y'/y = "+A+"*ln(x)+"+A);
        add("Isolate the derivative","Multiply the whole right side by y.","y' = y*("+A+"*ln(x)+"+A+")");
        add("Substitute and factor","Replace y using the original function.",p.answer,"Do not treat the exponent as constant.");
        p.check="Rewriting y as e^("+A+"x ln(x)) gives the same derivative by the chain rule.";
    }else if(topic==8&&level==1){
        int k=a*a+a*b+b*b;
        p.prompt="Find dy/dx, then evaluate the slope at ("+A+", "+B+").";
        p.math="x^2+x*y+y^2 = "+s(k);p.answer="y' = -(2*x+y)/(x+2*y)";
        p.conclusion="Slope at the point: "+fraction(-(2*a+b),a+2*b)+".";
        add("Verify the point","Check that the coordinates satisfy the equation.",s(a*a)+"+"+s(a*b)+"+"+s(b*b)+" = "+s(k));
        add("Differentiate the mixed product","Treat y as a function of x.","DERIV[x*y] = y+x*y'");
        add("Differentiate the full equation","The derivative of y squared requires the chain rule.","2*x+y+x*y'+2*y*y' = 0");
        add("Collect derivative terms","Factor out y' before dividing.","(x+2*y)*y' = -(2*x+y)");
        add("Solve for the derivative","The formula holds where its denominator is nonzero.",p.answer);
        add("Evaluate the slope","Now substitute the coordinates.","y' = "+fraction(-(2*a+b),a+2*b),"Substituting the point before differentiating would turn the equation into constants.");
        p.check="Both coordinates are positive, so the slope formula gives a negative value.";
    }else if(topic==8){
        p.prompt="Find the second derivative at (0, "+A+") on this circle.";
        p.math="x^2+y^2 = "+s(a*a);p.answer="y'' = -1/"+A;
        add("Differentiate once implicitly","Remember the derivative of y depends on x.","2*x+2*y*y' = 0");
        add("Evaluate the first derivative","Solve before substituting the point.","y' = -x/y = 0");
        add("Differentiate again","Use the product rule on y times y'.","2+2*(y')^2+2*y*y'' = 0");
        add("Solve for the second derivative","Isolate the highest derivative.","y'' = -(1+(y')^2)/y");
        add("Evaluate at the point","Use y = "+A+" and y' = 0.",p.answer,"The second derivative of y squared is not just 2y''.");
        p.check="The top of the circle is concave down, so a negative second derivative is expected.";
    }else if(topic==9&&level==1){
        p.prompt="Find the tangent line at (1, "+s(a+1)+").";
        p.math="y = x^3+"+A+"/x";p.answer="y-"+s(a+1)+" = ("+s(3-a)+")*(x-1)";
        add("Verify the point","Evaluate the original function at x = 1.","y(1) = 1+"+A+" = "+s(a+1));
        add("Rewrite the reciprocal","Use a negative exponent to track its derivative.","y = x^3+"+A+"x^(-1)");
        add("Differentiate","Apply the power rule to both terms.","y' = 3*x^2-"+A+"/x^2");
        add("Evaluate the slope","A tangent slope is the derivative at the specified point.","m = 3-"+A+" = "+s(3-a));
        add("Write point-slope form","Use the point and slope together.",p.answer);
        p.check="Substituting x = 1 in the line recovers the given y-coordinate.";
    }else if(topic==9){
        p.prompt="Find the normal line to the implicit curve at ("+A+", "+B+").";
        p.math="x^2+x*y+y^2 = "+s(a*a+a*b+b*b);
        p.answer="y-"+B+" = ("+fraction(a+2*b,2*a+b)+")*(x-"+A+")";
        add("Differentiate implicitly","Use a product rule for the mixed term.","2*x+y+x*y'+2*y*y' = 0");
        add("Find the tangent-slope formula","Collect all y' terms.","y' = -(2*x+y)/(x+2*y)");
        add("Evaluate at the point","Substitute both coordinates after differentiating.","m = "+fraction(-(2*a+b),a+2*b));
        add("Find the normal slope","Use the negative reciprocal of the tangent slope.","m_n = "+fraction(a+2*b,2*a+b),"The normal slope is not generally just the negative tangent slope.");
        add("Write point-slope form","The normal passes through the same point.",p.answer);
        add("Verify perpendicularity","The product of the two nonzero slopes must be negative one.","("+fraction(-(2*a+b),a+2*b)+")*("+fraction(a+2*b,2*a+b)+") = -1");
        p.check="Substitute the given x-coordinate in the line to recover the given y-coordinate. The tangent and normal slopes multiply to -1.";
    }else if(topic==10&&level==1){
        p.prompt="Find local and absolute extrema on the closed interval [-"+s(a+1)+", "+s(a+1)+"].";
        p.math="f(x) = x^3-"+s(3*a*a)+"x";
        p.answer="f(-"+A+") = "+s(2*a*a*a)+", f("+A+") = -"+s(2*a*a*a);
        p.conclusion="Local and absolute maximum at x = -"+A+"; local and absolute minimum at x = "+A+".";
        add("Differentiate and factor","Critical numbers occur where the derivative vanishes or does not exist.","f'(x) = 3*(x-"+A+")*(x+"+A+")");
        add("Find critical numbers","Both lie in the given interval.","x = -"+A+", x = "+A);
        add("Classify by sign changes","The first derivative is positive, then negative, then positive. Thus the left critical point is a local maximum and the right is a local minimum.","f' : +, -, +");
        add("Evaluate interior candidates","Use the original function.",p.answer);
        add("Evaluate endpoints","Absolute extrema on a closed interval require endpoint comparisons.","f(-"+s(a+1)+") = "+s(2*a*a*a-3*a-1)+", f("+s(a+1)+") = "+s(-2*a*a*a+3*a+1),"A local-extremum test alone does not settle an absolute-extremum question.");
        add("Compare all four values","The interior critical values are the largest and smallest.","max = "+s(2*a*a*a)+", min = -"+s(2*a*a*a));
        p.check="The cubic is odd and the interval symmetric, so the absolute extreme values are opposites.";
    }else if(topic==10){
        p.prompt="Find increase/decrease intervals, local extrema, concavity intervals, and inflection points.";
        p.math="f(x) = x/(x^2+"+s(a*a)+")";
        p.answer="f'(x) = ("+s(a*a)+"-x^2)/(x^2+"+s(a*a)+")^2";
        p.conclusion="Increasing: (-"+A+", "+A+").\nDecreasing: (-infinity, -"+A+") and ("+A+", infinity).\nLocal minimum: (-"+A+", -1/"+s(2*a)+"); local maximum: ("+A+", 1/"+s(2*a)+").\nConcave down: (-infinity, -"+A+"sqrt(3)) and (0, "+A+"sqrt(3)).\nConcave up: (-"+A+"sqrt(3), 0) and ("+A+"sqrt(3), infinity).\nInflection points: (-"+A+"sqrt(3), -sqrt(3)/"+s(4*a)+"), (0, 0), ("+A+"sqrt(3), sqrt(3)/"+s(4*a)+").";
        add("Differentiate the quotient","The denominator is positive everywhere, so the numerator controls the derivative sign.",p.answer);
        add("Analyze the first derivative","Its numerator is positive between the two roots, negative outside. The left root is a local minimum and the right is a local maximum.","x = -"+A+", x = "+A);
        add("Differentiate again and factor","Use the quotient rule or a negative power.","f''(x) = 2*x*(x^2-"+s(3*a*a)+")/(x^2+"+s(a*a)+")^3");
        add("Find inflection candidates","Only the numerator can vanish.","x = -"+A+"*sqrt(3), 0, "+A+"*sqrt(3)");
        add("Test signs in four intervals","From left to right, the second derivative is negative, positive, negative, positive. Each candidate changes concavity.","f'' : -, +, -, +","A zero second derivative alone does not guarantee an inflection point.");
        add("State concavity intervals","Concave down on (-infinity, -"+A+"sqrt(3)) and (0, "+A+"sqrt(3)); concave up on (-"+A+"sqrt(3), 0) and ("+A+"sqrt(3), infinity).");
        add("Evaluate the inflection points","Substitute all three x-values into the original function.","(-"+A+"*sqrt(3),-sqrt(3)/"+s(4*a)+"), (0,0), ("+A+"*sqrt(3),sqrt(3)/"+s(4*a)+")");
        p.check="The original function is odd, its first derivative even, and its second derivative odd.";
    }else if(topic==11&&level==1){
        int f=pick(8,16)*4;
        p.prompt="A farmer has "+s(f)+" m of fencing for three sides of a rectangular field beside a straight river. The river side needs no fence. Find the dimensions maximizing area.";
        p.math="2*x+y = "+s(f);p.answer="x = "+s(f/4)+", y = "+s(f/2)+", A = "+s(f*f/8);
        p.conclusion="The two perpendicular sides are "+s(f/4)+" m each; the parallel side is "+s(f/2)+" m. Maximum area: "+s(f*f/8)+" square meters.";
        add("Define variables","Let x denote each perpendicular side and y the fenced parallel side.","2*x+y = "+s(f),"Only three sides use fencing.");
        add("Use the constraint","Express the parallel side in terms of x.","y = "+s(f)+"-2*x");
        add("Build the objective and domain","Both side lengths must be positive.","A(x) = "+s(f)+"x-2*x^2, 0 < x < "+s(f/2));
        add("Find the critical point","Differentiate and set the result to zero.","A'(x) = "+s(f)+"-4*x = 0");
        add("Verify a global maximum","The area is strictly concave down throughout the feasible interval.","A''(x) = -4 < 0");
        add("Find dimensions and area","Substitute the optimal x into the constraint and area.",p.answer);
        p.check="The three fenced sides add to exactly "+s(f)+" m.";
    }else if(topic==11){
        int side=pick(3,7)*6,cut=side/6;
        p.prompt="An open-top box is made from a square sheet of side "+s(side)+" cm. Equal squares of side x are cut from the corners and the sides folded up. Find the cut size maximizing volume.";
        p.math="V(x) = x*("+s(side)+"-2*x)^2";
        p.answer="x = "+s(cut)+", V = "+s(cut*(side-2*cut)*(side-2*cut));
        p.conclusion="Cut out "+s(cut)+" cm squares. Box dimensions: "+s(side-2*cut)+" by "+s(side-2*cut)+" by "+s(cut)+" cm.";
        add("Model the geometry","The height is x; each base side loses two cut lengths.","V(x) = x*("+s(side)+"-2*x)^2");
        add("State the physical domain","The height and base dimensions must be positive.","0 < x < "+s(side/2));
        add("Differentiate and factor","Use the product and chain rules.","V'(x) = ("+s(side)+"-2*x)*("+s(side)+"-6*x)");
        add("Find candidates","Only the smaller derivative root is an interior point.","x = "+s(cut)+", x = "+s(side/2));
        add("Check the sign change","Inside the domain, the first factor is positive; the second changes from positive to negative at the interior root.","V' : +, -");
        add("Check boundary behavior","The limiting volume is zero at both ends.","V(0) = 0, V("+s(side/2)+") = 0","The endpoint derivative root describes a collapsed box.");
        add("Compute dimensions and volume","Use the original geometric model.",p.answer);
        p.check="The optimal cut is one sixth of the sheet side, and the base side is four times the box height.";
    }else if(topic==12&&level==1){
        p.prompt="Find the indefinite integral. Simplify first. Assume x > 0.";
        p.math="INT[||("+A+"x^3+"+B+"x+"+C+")/x^2|x]";
        p.answer="("+A+"/2)*x^2+"+B+"*ln(x)-"+C+"/x+C";
        add("Split the quotient","Divide each numerator term by x squared.","("+A+"x^3+"+B+"x+"+C+")/x^2 = "+A+"x+"+B+"/x+"+C+"x^(-2)");
        add("Recognize the exceptional power","One over x integrates to a logarithm.","INT[||1/x|x] = ln(x)+C","The integration power rule does not apply to exponent -1.");
        add("Integrate the linear term","Increase the exponent and divide by the new exponent.","INT[||"+A+"x|x] = ("+A+"/2)*x^2+C");
        add("Integrate the negative power","Increasing -2 to -1 introduces a negative coefficient.","INT[||"+C+"x^(-2)|x] = -"+C+"/x+C");
        add("Combine with one constant","All arbitrary constants merge into a single C.",p.answer);
        p.check="Differentiation returns "+A+"x + "+B+"/x + "+C+"/x^2.";
    }else if(topic==12){
        p.prompt="Find the indefinite integral, accounting for each inner coefficient.";
        p.math="INT[||"+A+"*e^("+B+"x)-"+B+"*sin("+A+"x)+1/(1+x^2)|x]";
        p.answer="("+A+"/"+B+")*e^("+B+"x)+("+B+"/"+A+")*cos("+A+"x)+atan(x)+C";
        add("Separate by linearity","Integrate the three terms independently.");
        add("Integrate the exponential","Divide by the coefficient in the exponent to undo the chain rule.","INT[||"+A+"*e^("+B+"x)|x] = ("+A+"/"+B+")*e^("+B+"x)+C");
        add("Integrate negative sine","Cosine differentiates to negative sine; divide by its inner coefficient.","INT[||-"+B+"*sin("+A+"x)|x] = ("+B+"/"+A+")*cos("+A+"x)+C");
        add("Recognize the inverse-trig form","This rational expression is the derivative of arctangent.","INT[||1/(1+x^2)|x] = atan(x)+C");
        add("Combine the results","Use one arbitrary constant.",p.answer);
        p.check="Differentiate term by term: each inner coefficient cancels its compensating denominator.";
    }else if(topic==13&&level==1){
        p.prompt="Find both the signed integral and total geometric area between the graph and the x-axis on the interval.";
        p.math="INT[0|"+s(2*a)+"|x-"+A+"|x]";p.answer="I = 0, A = "+s(a*a);
        add("Find the sign change","Locate the x-axis crossing.","x-"+A+" = 0");
        add("Find an antiderivative","Integrate the linear function.","F(x) = x^2/2-"+A+"x");
        add("Evaluate the signed integral","Subtract the lower endpoint value.","I = F("+s(2*a)+")-F(0) = 0");
        add("Find the signed left region","The graph lies below the axis until the crossing.","INT[0|"+A+"|x-"+A+"|x] = -"+fraction(a*a,2));
        add("Add positive geometric areas","The two triangular areas have the same positive size.","A = "+fraction(a*a,2)+"+"+fraction(a*a,2)+" = "+s(a*a),"Zero net integral does not mean zero area.");
        p.check="Two triangles, each of base "+A+" and height "+A+", have the same total area.";
    }else if(topic==13){
        p.prompt="Evaluate by splitting the interval at the relevant zeros inside the absolute value.";
        p.math="INT[-"+A+"|"+s(2*a)+"|abs(x^2-"+s(a*a)+")|x]";p.answer=fraction(8*a*a*a,3);
        add("Find the zeros","Factor the polynomial inside the absolute value.","x^2-"+s(a*a)+" = (x-"+A+")*(x+"+A+")");
        add("Determine signs","On this interval the polynomial is negative from -"+A+" to "+A+", and nonnegative from "+A+" to "+s(2*a)+".");
        add("Split the integral","Negate the polynomial where it is negative.","INT[-"+A+"|"+A+"|"+s(a*a)+"-x^2|x] + INT["+A+"|"+s(2*a)+"|x^2-"+s(a*a)+"|x]","Integrating the unmodified polynomial would give a different answer.");
        add("Integrate the middle region","Evaluate "+s(a*a)+"x - x^3/3 at both bounds.","I_1 = "+fraction(4*a*a*a,3));
        add("Integrate the right region","Evaluate x^3/3 - "+s(a*a)+"x at its bounds.","I_2 = "+fraction(4*a*a*a,3));
        add("Add the contributions","Both subintegrals now represent nonnegative area.","I = "+fraction(4*a*a*a,3)+"+"+fraction(4*a*a*a,3)+" = "+p.answer);
        p.check="The original integrand is nonnegative and the result is positive.";
    }else if(topic==14&&level==1){
        p.prompt="Evaluate by substitution.";
        p.math="INT[||x/(x^2+"+A+")|x]";p.answer="(1/2)*ln(x^2+"+A+")+C";
        add("Choose the inner expression","Its derivative matches the numerator up to a constant.","u = x^2+"+A);
        add("Transform the differential","Solve for the factor actually present.","du = 2*x*dx, x*dx = du/2");
        add("Rewrite the entire integral","No x terms should remain.","(1/2)*INT[||1/u|u]");
        add("Integrate in u","Use the reciprocal antiderivative.","(1/2)*ln(abs(u))+C");
        add("Substitute back","The quadratic is positive for all real x, so absolute-value bars are unnecessary.",p.answer,"Do not lose the factor one half.");
        p.check="Differentiate: the factor 2x from the logarithm's argument cancels the one half.";
    }else if(topic==14){
        p.prompt="Evaluate by substitution, changing the integration bounds.";
        p.math="INT[0|1|x^2*e^("+A+"x^3)|x]";p.answer="(e^"+A+"-1)/"+s(3*a);
        add("Choose the exponent","Its derivative contains the x-squared factor.","u = "+A+"x^3");
        add("Transform the differential","Keep the compensating constant outside.","du = "+s(3*a)+"x^2*dx");
        add("Change both bounds","Evaluate u at each original x bound.","x = 0: u = 0; x = 1: u = "+A,"Do not keep x-bounds with a u-integrand.");
        add("Write the transformed integral","The bounds and integrand now use u.","(1/"+s(3*a)+")*INT[0|"+A+"|e^u|u]");
        add("Evaluate","The antiderivative of e to u is itself.","(e^"+A+"-e^0)/"+s(3*a)+" = "+p.answer);
        p.check="The integrand is nonnegative on [0,1], so the answer must be positive.";
    }else if(topic==15&&level==1){
        p.prompt="Differentiate without finding an antiderivative.";
        p.math="G(x) = INT["+A+"|x^2|sqrt(1+t^4)|t]";p.answer="G'(x) = 2*x*sqrt(1+x^8)";
        add("Check continuity","The integrand is continuous everywhere, so the Fundamental Theorem applies.");
        add("Identify the moving bound","Only the upper limit depends on x.","g(x) = x^2");
        add("Substitute into the integrand","Replace every t by the upper-limit expression.","sqrt(1+(x^2)^4) = sqrt(1+x^8)");
        add("Differentiate the upper bound","Multiply by its derivative, using the chain rule.","g'(x) = 2*x","Substitution alone misses this factor.");
        add("Combine","The constant lower bound contributes zero.",p.answer);
        p.check="At x = 0 the bound's derivative is zero, so the full derivative is zero too.";
    }else if(topic==15){
        p.prompt="Differentiate with two variable bounds. Do not seek an antiderivative.";
        p.math="H(x) = INT[sin(x)|x^3|e^("+A+"t^2)|t]";
        p.answer="H'(x) = 3*x^2*e^("+A+"x^6)-cos(x)*e^("+A+"*sin(x)^2)";
        add("Check continuity","The exponential integrand is continuous for all real t.");
        add("Split at a constant reference point","Subtract the lower-bound integral from the upper-bound integral.","H(x) = INT[0|x^3|e^("+A+"t^2)|t] - INT[0|sin(x)|e^("+A+"t^2)|t]");
        add("Differentiate the upper contribution","Substitute x cubed for t and multiply by the derivative of x cubed.","3*x^2*e^("+A+"x^6)");
        add("Differentiate the lower contribution","Substitute sine for t, multiply by cosine, and retain the minus sign.","-cos(x)*e^("+A+"*sin(x)^2)","A moving lower bound contributes a subtraction.");
        add("Combine","The integrand is evaluated at each bound; it is not itself differentiated.",p.answer);
        p.check="The Fundamental Theorem works here even though no elementary antiderivative is available.";
    }else if(topic==16&&level==1){
        int k=pick(1,4),v=pick(1,3);
        p.prompt="A "+s(5*k)+" m ladder leans against a wall. Its base moves away at "+s(v)+" m/s. Find the signed vertical velocity of the top when the base is "+s(3*k)+" m from the wall.";
        p.math="x^2+y^2 = "+s(25*k*k);p.answer="dy/dt = "+fraction(-3*v,4);
        p.conclusion="The top moves downward at "+fraction(3*v,4)+" m/s.";
        add("Define the quantities","Let x be the base distance and y the top's height. The ladder length is fixed.","dx/dt = "+s(v));
        add("Find the height at this instant","Use the Pythagorean relation.","y = sqrt("+s(25*k*k)+"-"+s(9*k*k)+") = "+s(4*k));
        add("Differentiate with respect to time","Both x and y vary with time.","2*x*(dx/dt)+2*y*(dy/dt) = 0");
        add("Isolate the unknown rate","Rearrange before substituting.","dy/dt = -(x/y)*(dx/dt)");
        add("Substitute and interpret","A negative height rate means downward motion.",p.answer,"Keep units and the negative sign.");
        p.check="Moving the base outward makes the top move downward, as the sign indicates.";
    }else if(topic==16){
        int h=pick(2,5),v=pick(2,6),k=pick(2,3);
        p.prompt="Water enters an inverted conical tank at "+s(v)+" cubic meters per minute. The tank has height "+s(4*k)+" m and top radius 4 m. Find the water-level rate when its depth is "+s(h)+" m.";
        p.math="V = (1/3)*pi*r^2*h";p.answer="dh/dt = "+fraction(v*k*k,h*h)+"/pi";
        p.conclusion="The water rises at "+fraction(v*k*k,h*h)+" / pi meters per minute.";
        add("Relate radius and depth","Similar triangles give the same ratio for the water and the tank.","r/h = 1/"+s(k));
        add("Eliminate the changing radius","Express volume using depth alone.","V = pi*h^3/"+s(3*k*k),"The water radius changes with depth; it is not constant.");
        add("Differentiate with respect to time","Use the chain rule on h cubed.","dV/dt = (pi*h^2/"+s(k*k)+")*(dh/dt)");
        add("Solve for the depth rate","Isolate the requested rate before substituting.","dh/dt = ("+s(k*k)+"/(pi*h^2))*(dV/dt)");
        add("Use the instantaneous depth","Insert the depth and inflow, not the tank's full height.",p.answer);
        p.check="The formula decreases with depth squared: a larger surface area rises more slowly under the same inflow.";
    }else if(topic==17&&level==1){
        p.prompt="Define f by the displayed quotient for x != "+A+". Find the value of f("+A+") that makes f continuous, then find f'("+A+").";
        p.math="f(x) = (x^3-"+s(a*a*a)+")/(x-"+A+")";
        p.answer="f("+A+") = "+s(3*a*a)+", f'("+A+") = "+s(3*a);
        add("Identify the missing value","The displayed formula is undefined at the specified point. Continuity requires filling it with the limit.");
        add("Factor a difference of cubes","Use the cubic identity to expose the removable factor.","x^3-"+s(a*a*a)+" = (x-"+A+")*(x^2+"+A+"x+"+s(a*a)+")");
        add("Cancel for nearby x","The simplified expression agrees with the quotient whenever x differs from "+A+".","f(x) = x^2+"+A+"x+"+s(a*a));
        add("Choose the continuous value","Evaluate the simplified polynomial at the missing point.","f("+A+") = "+s(3*a*a));
        add("Differentiate the extension","With this value filled in, the entire function is the polynomial, including at the former hole.","f'(x) = 2*x+"+A);
        add("Evaluate the requested derivative","Substitute the point into the derivative.","f'("+A+") = "+s(3*a),"Differentiate the continuous extension, not an expression that still has a hole.");
        p.check="A polynomial is differentiable everywhere, so the extended function has no remaining discontinuity.";
    }else if(topic==17){
        p.prompt="For x < "+A+", let f(x) = x^2. For x >= "+A+", let f(x) = m*x + b. Find m and b so f is differentiable at the joining point.";
        p.math="f_L(x) = x^2, f_R(x) = m*x+b";
        p.answer="m = "+s(2*a)+", b = -"+s(a*a);
        add("Require continuity first","Differentiability implies continuity, so the two formulas must meet.","m*"+A+"+b = "+s(a*a));
        add("Match the left derivative","The derivative on the quadratic side is 2x.","f'_L("+A+") = "+s(2*a));
        add("Match the right derivative","The derivative of the linear side is m.","f'_R("+A+") = m");
        add("Solve the slope condition","Equal one-sided derivative limits determine m.","m = "+s(2*a),"Matching slopes alone is insufficient if the pieces do not meet.");
        add("Solve the value condition","Insert m into the continuity equation.","b = "+s(a*a)+"-"+s(2*a*a)+" = -"+s(a*a));
        add("State both parameters","Both continuity and derivative matching are now satisfied.",p.answer);
        p.check="The linear piece is the tangent line to y = x squared at the joining point.";
    }else if(topic==18&&level==1){
        int right=a+2;
        p.prompt="Verify the Mean Value Theorem applies on [1, "+s(right)+"], then find every c in the open interval satisfying its conclusion.";
        p.math="f(x) = x^3";
        int slope=right*right+right+1;
        p.answer="c = sqrt("+s(slope)+"/3)";
        add("Check the hypotheses","A polynomial is continuous on the closed interval and differentiable on the open interval. Both theorem conditions hold.");
        add("Compute the average slope","Use the secant slope across the whole interval.","(f("+s(right)+")-f(1))/("+s(right)+"-1) = "+s(slope));
        add("Find the derivative","The theorem compares an instantaneous slope to the secant slope.","f'(x) = 3*x^2");
        add("Set slopes equal","Solve for points where the derivative matches the average slope.","3*c^2 = "+s(slope));
        add("Enforce the open interval","Only the positive square root lies between 1 and "+s(right)+".",p.answer,"A theorem candidate outside the interval is not a valid answer.");
        p.check="The quantity under the square root lies strictly between 1 and "+s(right*right)+", which confirms 1 < c < "+s(right)+".";
    }else if(topic==18){
        int base=a*a,delta=pick(1,3);
        p.prompt="Use linearization of sqrt(x) at x = "+s(base)+" to approximate sqrt("+s(base)+"."+s(delta)+"). State whether the approximation is an overestimate or underestimate.";
        p.math="f(x) = sqrt(x)";
        p.answer="L("+s(base)+"."+s(delta)+") = "+A+"+"+fraction(delta,20*a);
        p.conclusion="Overestimate, because sqrt(x) is concave down for x > 0.";
        add("Choose the nearby exact point","At the specified perfect square, both the function value and derivative are easy.","f("+s(base)+") = "+A);
        add("Find the local slope","Differentiate the square-root function.","f'(x) = 1/(2*sqrt(x))");
        add("Evaluate the slope","Use the base point, not the target point.","f'("+s(base)+") = 1/"+s(2*a));
        add("Build the linearization","A linearization is the tangent line at the base point.","L(x) = "+A+"+(1/"+s(2*a)+")*(x-"+s(base)+")");
        add("Substitute the target","The change in x is "+s(delta)+"/10, not "+s(delta)+".",p.answer);
        add("Determine the error direction","The second derivative is negative. A tangent line lies above a concave-down curve.","f''(x) = -1/(4*x^(3/2))","The concavity determines the direction, not just the slope.");
        p.check="The approximation is slightly larger than "+A+", since the target is slightly above its square.";
    }else if(topic==19&&level==1){
        p.prompt="A particle has the acceleration shown. At t = 0 its velocity is "+B+" and position is "+C+". Find its velocity and position functions.";
        p.math="a(t) = "+s(6*a)+"t-"+s(2*b);
        p.answer="v(t) = "+s(3*a)+"t^2-"+s(2*b)+"t+"+B+", s(t) = "+A+"t^3-"+B+"t^2+"+B+"t+"+C;
        add("Integrate acceleration","Velocity is an antiderivative of acceleration.","v(t) = "+s(3*a)+"t^2-"+s(2*b)+"t+C_1");
        add("Use the initial velocity","Substitute t = 0 to determine the first integration constant.","C_1 = "+B);
        add("Integrate velocity","Position is an antiderivative of the complete velocity, including its constant.","s(t) = "+A+"t^3-"+B+"t^2+"+B+"t+C_2");
        add("Use the initial position","Substitute t = 0 into the position expression.","C_2 = "+C);
        add("State both functions","Each integration has its own constant, determined by its own initial condition.",p.answer,"Do not reuse a single arbitrary constant for two integrations.");
        p.check="Differentiate position to recover velocity, then differentiate velocity to recover acceleration. Both initial conditions hold.";
    }else if(topic==19){
        p.prompt="A particle has the velocity shown for 0 <= t <= "+s(3*a)+". Find its displacement and total distance traveled.";
        p.math="v(t) = (t-"+A+")*(t-"+s(2*a)+")";
        p.answer="D = "+fraction(3*a*a*a,2)+", T = "+fraction(11*a*a*a,6);
        add("Locate direction changes","Velocity is zero at two interior times.","t = "+A+", t = "+s(2*a));
        add("Determine velocity signs","The motion is forward, then backward, then forward. Distance requires absolute velocity.","v : +, -, +");
        add("Find a velocity antiderivative","Expand the product and integrate.","F(t) = t^3/3-("+s(3*a)+"/2)*t^2+"+s(2*a*a)+"t");
        add("Compute displacement","Integrate signed velocity over the full interval.","D = F("+s(3*a)+")-F(0) = "+fraction(3*a*a*a,2));
        add("Find the negative contribution","The middle interval is traveled in the negative direction.","INT["+A+"|"+s(2*a)+"|(t-"+A+")*(t-"+s(2*a)+")|t] = -"+fraction(a*a*a,6));
        add("Convert displacement to total distance","Replace the negative contribution by its positive size, adding twice its magnitude.","T = "+fraction(3*a*a*a,2)+"+2*("+fraction(a*a*a,6)+") = "+fraction(11*a*a*a,6),"Integrating velocity gives displacement, not necessarily total distance.");
        p.check="Total distance exceeds the magnitude of displacement because the particle reverses direction.";
    }else if(topic==20&&level==1){
        p.prompt="Evaluate with L'Hopital's rule. Check the indeterminate form each time before applying the rule.";
        p.math="LIM[x|0|(e^("+A+"x)-1-"+A+"x)/x^2]";p.answer=fraction(a*a,2);
        add("Verify the initial form","Both numerator and denominator approach zero. They are differentiable near zero, and the denominator derivative is nonzero away from zero.");
        add("Apply the rule once","Differentiate numerator and denominator separately.","LIM[x|0|("+A+"*e^("+A+"x)-"+A+")/(2*x)]","This is not the quotient rule.");
        add("Recheck the form","The new quotient still gives 0/0, so a second application is justified.");
        add("Apply the rule again","Differentiate each part again.","LIM[x|0|("+s(a*a)+"*e^("+A+"x))/2]");
        add("Evaluate the continuous result","The exponential tends to one.",p.answer);
        p.check="The subtracted constant and linear terms leave a quadratic leading contribution.";
    }else if(topic==20){
        p.prompt="Evaluate the one-sided limit. Transform the variable power with logarithms.";
        p.math="LIM[x|0+|x^("+A+"x)]";p.answer="1";
        add("Recognize the indeterminate power","The base tends to zero while the exponent tends to zero. The form 0^0 does not determine the limit.");
        add("Take a logarithm","For x > 0 the expression is positive.","y = x^("+A+"x), ln(y) = "+A+"x*ln(x)");
        add("Rewrite the product as a quotient","This creates a form to which L'Hopital's rule applies.","ln(y) = ("+A+"*ln(x))/(1/x)");
        add("Check the form and differentiate","The quotient has infinite numerator and denominator magnitudes. Differentiate each separately.","("+A+"/x)/(-1/x^2) = -"+A+"x");
        add("Evaluate the logarithm's limit","The transformed quotient tends to zero.","LIM[x|0+|ln(y)] = 0");
        add("Undo the logarithm","Continuity of the exponential converts the logarithm limit back to the original limit.","LIM[x|0+|y] = e^0 = 1","A limit of zero for ln(y) means a limit of one for y.");
        p.check="For small positive x, the exponent times ln(x) approaches zero from below, so the original expression approaches one from below.";
    }else throw std::invalid_argument("Unknown exam topic");
    return p;
}
