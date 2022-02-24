package com.ay.test.controller;

import com.ay.controller.AyTestController;
import org.junit.Test;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;
import org.springframework.stereotype.Service;

@Service
public class AyTestControllerTest {
    @Test
    public void testSpring() {
        ApplicationContext cxt =
                new ClassPathXmlApplicationContext("applicationContext.xml");
        AyTestController ayTestController = (AyTestController) cxt.getBean("ayTestController");
        System.out.println(ayTestController.sayHello());

    }
}
