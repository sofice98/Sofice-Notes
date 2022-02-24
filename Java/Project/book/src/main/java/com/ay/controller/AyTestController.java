package com.ay.controller;

import org.junit.Test;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
@RequestMapping(value = "/test")
public class AyTestController {
    @GetMapping("/ay")
    public String sayHello() {
        return "hello";
    }
}
