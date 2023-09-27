export const IfElseExamples = [
    {
        title: 'If Statement (Single Statement):',
        codeSnippet: `
let isRaining = true;

if (isRaining)
  print('Bring an umbrella.');  // Single statement without braces
`,
        description: "In this example, we have a variable isRaining that is set to true. The if statement checks if it's raining (the condition is true). If the condition is true, it executes the single statement inside the if block, which advises to bring an umbrella."
    },
    {
        title: 'If-Else Statement:',
        codeSnippet: `
        let isSunny = false;

        if (isSunny) {
          print('Wear sunglasses.');
        } else {
          print('Grab an umbrella.');
        }
        `,
        description: "Here, we have a variable isSunny set to false. The if-else statement checks the condition. If isSunny is true, it advises wearing sunglasses; otherwise, if isSunny is false, it suggests grabbing an umbrella."
    },
    {
        title: 'Chained If-Else Statement:',
        codeSnippet: `
        let temperature = 28;

        if (temperature < 0) {
          print('Freezing cold!');
        } else if (temperature >= 0 && temperature <= 20) {
          print("It's a bit chilly.");
        } else if (temperature > 20 && temperature <= 30) {
          print('Pleasant weather.');
        } else {
          print("It's getting hot!");
        }
        `,
        description: "In this example, we use a chained if-else statement to provide different messages based on the temperature. Depending on the temperature value stored in the temperature variable, it selects an appropriate message to display. If none of the conditions match, the final else block executes to indicate that it's getting hot."
    }
];

export const ConditionalOperatorExamples = [
    {
        title: 'Conditional Operator (Ternary Operator):',
        codeSnippet: `
        let age = 25;
        let message = (age >= 18) ? 'You are an adult' : 'You are not an adult';
        
        print(message);
        `,
        description: " In this example, we use the conditional (ternary) operator ? to check if the age variable is greater than or equal to 18. If it's true, it assigns the message 'You are an adult'; otherwise, it assigns 'You are not an adult'."
    },
    {
        title: 'Chained Conditional Operator:',
        codeSnippet: `
        let score = 75;
        let grade = (score >= 90)
          ? 'A'
          : (score >= 80)
          ? 'B'
          : (score >= 70)
          ? 'C'
          : (score >= 60)
          ? 'D'
          : 'F';
        
        print('Your grade is', grade);
        `,
        description: "In this example, we have a series of chained conditional operators ? to determine a student's grade based on their score. It first checks if the score is greater than or equal to 90, and if true, assigns 'A'. If not, it proceeds to the next condition until it finds a match or assigns 'F' if none of the conditions match."
    }
]