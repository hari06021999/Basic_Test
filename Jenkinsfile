node {
    try {
        checkout scm
        stage('Preparation') {
           sh 'ceedling clean'
        }
        
        stage('Unit Test') {
            dir("2W_Test") {
                sh 'ceedling test:all'
            }
        }
        stage('Coverage Test') {
            dir("2W_Test") {
                sh 'ceedling gcov:all'
            }
        }
        stage('Coverage XML Generate') {
            dir("2W_Test") {
                 sh 'gcovr -r . --html --html-details -o CAN_Test_Details.html'
              
            }
        }
    }
   
    catch (e) {
        throw e
    }
      finally{
           emailext to: "hariprithi99@gmail.com",
            subject: "Test Email From Jenkins",
            body: "Hey Buddy you got mail! <br>  BUILD STATUS: ${currentBuild.currentResult}: Job ${env.JOB_NAME}\nMore Info can be found here: ${env.BUILD_URL}",
            attachLog: true,
            attachmentsPattern: "2W_Test/CAN_Test_Details.html",compressLog: true,
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
    
