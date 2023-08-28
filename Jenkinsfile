node {
    try {
        checkout scm
        // stage('Preparation') {
        //     sh 'mv 2W_Test/project.yml 2W_Test/project.yml.back'
        //     sh 'ceedling new test_suite' // prepare test_suite insiders
        //     sh 'mv test_suite/project.yml.back test_suite/project.yml'
        //     sh 'ceedling upgrade test_suite' // upgrade ceedling
        // }
        
        stage('Unit Test') {
            dir("2W_Test") {
                sh 'ceedling test:all'
                sh 'ceedling gcov:all'
                sh 'ceedling utils:gcov'
                // sh 'cat build/artifacts/gcov/GcovCoverageResults.xml'
            }
        }
    } 
}

// pipeline {
//     agent any 

//     environment {
//         TOOL_DIR = "${WORKSPACE}\\2W_Test\\src\\CICDTool"
//     }

//     stages {
//         stage('Build') { 
//             steps {
//                 bat "${TOOL_DIR}\\build.bat ${WORKSPACE}\\Debug Debug all"
//             }
//         }
        
    
       
//     }
//      post{
//         always{
//             emailext to: "hariprithi99@gmail.com",
//             subject: "Test Email From Jenkins",
//             body: "I Hope all of you getting Email's From Jenkins <br>  BUILD STATUS: ${currentBuild.currentResult}: Job ${env.JOB_NAME}\nMore Info can be found here: ${env.BUILD_URL}",
//             attachLog: true
//         }
//     }
     
   
       
// }
    
